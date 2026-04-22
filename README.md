# MICROEX

Exchange simulator with a live limit order book supporting limit/market orders, price-time priority, partial fills, and cancel/modify operations. Added deterministic replay and benchmarked event processing under simulated load, with correctness validated against edge-case scenarios.

> Added deterministic event replay and benchmarked order processing under simulated load while maintaining correctness across edge-case tests.

`C++` `ORDER_BOOK` `CONCURRENCY` `BENCHMARKING`

## Structure

```
models/       — Order, Trade, Event types
orderbook/    — Bid/ask book with price-time priority
engine/       — Matching logic
data/         — Sample CSV input
main.cpp      — Entry point
```

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Progress

- [x] Day 1 — Core models (`Order`, `Trade`, `Side`, `OrderType`)
- [x] Day 2 — Order book data structures (sorted bids/asks, FIFO per level)
- [ ] Day 3 — Limit order matching
- [ ] Day 4 — File/CLI input
- [ ] Day 5 — Correctness tests
