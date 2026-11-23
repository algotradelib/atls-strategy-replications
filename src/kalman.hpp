#pragma once

#include <cmath>
#include <limits>

namespace atls::user {

/**
 * @brief A Kalman filter of y on (x, 1) with an identity transition (Chan, Example 3.3): `kalman.atls`'s
 *   `extern indicator kalman`.
 *
 * The slope and intercept drift with variance delta / (1 - delta), and y is measured with variance ve.
 * Each update reports the forecast error and its deviation from before the correction, and the slope after it.
 *
 * Floating-point contraction is turned off in `update` under Clang; GCC needs `-ffp-contract=off` (cmdatl's
 * drivers pass it), MSVC `/fp:precise`.
 */
class kalman {
public:
  /**
   * @brief One prediction and correction; the first call also sets delta and ve and starts from a zero state.
   * @param y The regressand.
   * @param x The regressor.
   * @param delta The drift parameter, in [0, 1); read on the first call only.
   * @param ve The measurement variance, at least 0; read on the first call only.
   */
  void update(double y, double x, double delta, double ve) {
#if defined(__clang__)
#pragma clang fp contract(off)
#endif
    if (fresh_) {
      vw_ = delta / (1 - delta);
      ve_ = ve;
      // The first prediction adds vw_ back: the covariance starts at zero.
      r00_ = r11_ = -vw_;
      fresh_ = false;
    }
    // Predict: R += Vw, the forecast and its variance.
    r00_ += vw_;
    r11_ += vw_;
    const double forecast = x * b0_ + b1_;
    // x' R x with x = (x, 1), row by column.
    const double t0 = x * r00_ + r10_;
    const double t1 = x * r01_ + r11_;
    q_ = (t0 * x + t1) + ve_;
    // Correct: K = R x / Q, beta += K e, R -= K x' R.
    const double k0 = (r00_ * x + r01_) / q_;
    const double k1 = (r10_ * x + r11_) / q_;
    e_ = y - forecast;
    b0_ += k0 * e_;
    b1_ += k1 * e_;
    const double a00 = k0 * t0;
    const double a01 = k0 * t1;
    const double a10 = k1 * t0;
    const double a11 = k1 * t1;
    r00_ -= a00;
    r01_ -= a01;
    r10_ -= a10;
    r11_ -= a11;
  }
  /** @brief The slope after the last correction. */
  double beta() const {
    return b0_;
  }
  /** @brief The last forecast error. */
  double error() const {
    return e_;
  }
  /** @brief The last forecast error's deviation. */
  double sd() const {
    return std::sqrt(q_);
  }

private:
  /** @brief Whether no update has run yet. */
  bool fresh_{true};
  /** @brief The drift variance. */
  double vw_{0};
  /** @brief The measurement variance. */
  double ve_{0};
  /** @brief The slope. */
  double b0_{0};
  /** @brief The intercept. */
  double b1_{0};
  /** @brief The covariance, row 0, column 0. */
  double r00_{0};
  /** @brief The covariance, row 0, column 1. */
  double r01_{0};
  /** @brief The covariance, row 1, column 0. */
  double r10_{0};
  /** @brief The covariance, row 1, column 1. */
  double r11_{0};
  /** @brief The last forecast error. */
  double e_{std::numeric_limits<double>::quiet_NaN()};
  /** @brief The last forecast variance. */
  double q_{std::numeric_limits<double>::quiet_NaN()};
};

} // namespace atls::user
