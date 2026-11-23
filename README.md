# atls-strategy-replications

Replications of [Ernest P. Chan (2013), *Algorithmic Trading: Winning Strategies and Their Rationale*. Wiley](https://www.amazon.com/dp/1118460146), using atls with [cmdatl](https://github.com/algotradelib/cmdatl).

- Time series analytics (chapter 2)
  - [ ] Augmented Dickey-Fuller Test
  - [ ] Hurst Exponent and Variance Ratio Test
  - [ ] Half-life of Mean Reversion
  - [x] Cointegration and Johansen Test for Cointegration (`johansen-linear`: the trading rule, with the eigenvector and the half-life estimated elsewhere, over the whole sample, and given as parameters, so its figure looks ahead)
- Mean Reversion Strategies (chapter 3)
  - [x] Linear mean-reverting (`linear`, `linear-log`, `ratio`)
  - [x] Bollinger Bands (`bollinger`)
  - [x] Kalman Filter (`kalman`)
- Mean Reversion of Stocks and ETFs (chapter 4)
  - [x] Buy-on-Gap Model (`bog`)
  - [x] Cross-Sectional Linear Long-Short (`linear-longshort`/`longshort`)
  - [ ] Arbitrage between an ETF and Component Stocks
- Mean Reversion of Currencies and Futures (chapter 5)
  - [ ] Trading Currency Cross-Rates
  - [ ] Trading Futures Calendar Spread
  - [ ] Volatility futures versus Equity index futures
- Interday Momentum Strategies (chapter 6)
  - [x] Time series momentum (`tsmom`)
  - [x] Cross-sectional momentum (`xsmom`)
- Intraday Momentum Strategies (chapter 7)
  - [x] Opening gap and post-earnings announcement drift (`gap`, `pead`)

## Install

It needs [cmdatl](https://github.com/algotradelib/cmdatl#install) and [atlc](https://github.com/algotradelib/atlc#install); cmdatl finds atlc on `PATH`, or where `CMDATL_ATLC` names it.
atlc translates each program to C++ and cmdatl compiles it, so cmdatl also needs a C++17 compiler and CMake 3.20 or later; it compiles against the algotradelib it was built with ([algotradelib's install guide](https://github.com/algotradelib/algotradelib#install)).

## Running

```bash
cmdatl strategy backtest src/<strategy_name>.atls <daily|intraday>.toml ...
```

`kalman` runs with `kalman.toml`, which names its C++ (`src/kalman.hpp`):

```bash
cmdatl strategy backtest kalman.toml ...
```

## Acknowledgements

This project was developed with the assistance of generative AI tools.

## Disclaimer

This project is released under the MIT license; see [LICENSE](LICENSE).
The software is provided as is, without warranty of any kind, and the authors are not liable for any loss, including trading losses, arising from its use.
Nothing in this repository is investment advice.
