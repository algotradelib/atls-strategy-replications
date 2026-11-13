# atls-strategy-replications

Replications of [Ernest P. Chan (2013), *Algorithmic Trading: Winning Strategies and Their Rationale*. Wiley](https://www.amazon.com/dp/1118460146?lv=shuf&channelId=500&plpRedirect=mhFallback), using atls with [cmdatl](https://github.com/algotradelib/cmdatl).

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
- Interday Momentum Strategies (chapter 6)
  - [x] Time series momentum (`tsmom`)
  - [x] Cross-sectional momentum (`xsmom`)
- Mean Reversion of Currencies and Futures (chapter 5)
  - [ ] Trading Currency Cross-Rates
  - [ ] Trading Futures Calendar Spread
  - [ ] Volatility futures versus Equity index futures
- Intraday Momentum Strategies (chapter 7)
  - [x] Opening gap and post-earnings announcement drift (`gap`, `pead`)

Each name is a program in [`src/`](src), `<name>.atls`, run with one of two run specs: [`daily.toml`](daily.toml) (decided at a close and filled at that close, `fill = "decision-close"`) or [`intraday.toml`](intraday.toml) (each day replayed as a point at its open and the day's bar at its close, for `on_open` and `on_close`, with the same rule).

## Install

It needs [cmdatl](https://github.com/algotradelib/cmdatl#install) and [atlc](https://github.com/algotradelib/atlc#install); cmdatl finds atlc on `PATH`, or where `CMDATL_ATLC` names it.
atlc translates each program to C++ and cmdatl compiles it, so cmdatl also needs a C++17 compiler and CMake 3.20 or later; it compiles against the algotradelib it was built with ([algotradelib's install guide](https://github.com/algotradelib/algotradelib#install)).

## Running

Put the book's files in `data/` (git ignores it), then, from the project's root:

```bash
cmdatl strategy backtest src/<strategy_name>.atls <daily|intraday>.toml ...
```

Every strategy names its data on the command line, and any setting there wins over the run spec's: the daily ones their file and instruments (`bars.file=...`, `instruments.NAME=...`), the intraday ones the book's five stock tables (`bars.open=...`, `bars.high=...`, `bars.low=...`, `bars.close=...`, `bars.names=...`).
`gap` reads a long CSV instead (`bars.source=csv`, its columns named on the command line).
`pead` reads the five stock tables and, as its `data {}` value, the book's announcement calendar `earnannFile.csv` (`data.announced.file=data/earnannFile.csv`, `data.announced.layout=wide`, `data.announced.time=Date`, `data.announced.time_format=yyyymmdd`), between the calendar's first and last dates (`replay.from=20110103`, `replay.to=20120424`).
The calendar gives dates only: as in the book, a date's announcements are taken as known before that day's open, at 00:00 UTC (after the previous US close); the replication cannot check that assumption.
A relative path on the command line is read against the working directory.

## Acknowledgements

This project was developed with the assistance of generative AI tools.

## Disclaimer

This project is released under the MIT license; see [LICENSE](LICENSE).
The software is provided as is, without warranty of any kind, and the authors are not liable for any loss, including trading losses, arising from its use.
Nothing in this repository is investment advice.
