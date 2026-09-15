# Stock Exchange

A low-latency stock exchange and order matching engine prototype written in modern C++ (C++20).

## 📌 Project Overview

This project implements a stock exchange simulation designed with low-latency and deterministic performance principles:
- **Integer-based fixed-point arithmetic**: Eliminates floating-point precision issues and rounding errors (e.g. storing prices with a scaling factor).
- **Zero-exception design**: Built with `-fno-exceptions` (on GCC/Clang) and strict warnings to eliminate exception table lookups and avoid latency spikes.
- **Modular architecture**: Distinct executables for the exchange core, trader terminal, and market liquidity simulator.

---

## 📁 Repository Structure

```text
├── CMakeLists.txt              # CMake build configuration
├── info.txt                    # Quick build commands reference
├── src/
│   ├── core/
│   │   └── types.h             # Fundamental types (Price, Quantity, OrderId)
│   └── stock_exchange_main.cpp # Exchange engine entry point
└── tools/
    ├── trader_terminal.cpp     # CLI interface for submitting orders & monitoring
    └── liquidity_bot.cpp       # Automated bot to provide market depth/liquidity
```

---

## 🛠️ Prerequisites

- **C++ Compiler**: Supporting C++20 (GCC 11+, Clang 13+, or MSVC 2019+)
- **CMake**: Version 3.24 or higher
- **Build System**: [Ninja](https://ninja-build.org/) (recommended) or platform default

---

## 🚀 Building & Running

### 1. Configure the build
```bash
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -S . -B build
```

### 2. Compile
```bash
ninja -C build
```

### 3. Run Executables

- **Stock Exchange Engine**:
  ```bash
  ./build/src/stock_exchange
  ```
- **Trader Terminal**:
  ```bash
  ./build/tools/trader_terminal
  ```
- **Liquidity Bot**:
  ```bash
  ./build/tools/liquidity_bot
  ```

---

## 🗺️ Roadmap / In-Progress

- [ ] Order book data structures (Limit order book with price-time priority)
- [ ] Matching engine logic
- [ ] Inter-process or network communication between the exchange and clients
- [ ] Performance benchmarks and latency profiling

