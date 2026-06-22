# Chapter 27 — Multithreaded Programming with C++

> **Topic:** Concurrency in standard C++ — threads/`jthread`, the memory model
> and data races, atomics, mutexes and locks, condition variables,
> latches/barriers/semaphores, futures/promises, and coroutines.

## Samples

| # | Folder | What it demonstrates |
|---|--------|----------------------|
| 01 | `01_thread` | Launching threads from a function/functor/lambda/member, `thread_local`, C++20 `jthread` + `stop_token`, returning results, and propagating exceptions across threads. |
| 02 | `02_atomic` | `std::atomic` (`is_lock_free`, `fetch_add`, `compare_exchange_strong`), a data-race demo and its fixes via `atomic`/`atomic_ref`, and C++20 atomic wait/notify. |
| 03 | `03_mutex` | `atomic_flag` spinlock, `std::lock`/`scoped_lock`, `call_once`, `osyncstream` vs `lock_guard`/`timed_mutex`, and double-checked locking. |
| 04 | `04_latch` | `std::latch` as a finish line and as a starting gate. |
| 05 | `05_barrier` | A reusable `std::barrier` with a completion callback. |
| 06 | `06_semaphore` | `std::counting_semaphore` limiting concurrent access. |
| 07 | `07_future` | `promise`/`future`, `packaged_task`, `async`, future error handling, and `shared_future`. |
| 08 | `08_logger` | A condition-variable producer-consumer background logger — Version1 (no clean shutdown) and Version2 (graceful). |
| 09 | `09_coroutines` | A C++23 `std::generator` coroutine yielding values lazily with `co_yield`. |

## Build & run

```powershell
./run.ps1 -Chapter 27           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 27   # compile-check every sample (no run)
```

## Notes

- **Compiler note:** 12 samples gained `#include <chrono>` — they use chrono literals
  (`1ms`, `1s`) and the newest MSVC no longer pulls `<chrono>` in transitively via
  `<thread>`. Behavior is unchanged.
- **Intentional data-race demo:** `02_atomic/04_inc_func_non_atomic` (result varies / UB).
- **Intentional flaw:** `08_logger/Version1` never shuts the background thread down and
  calls `std::terminate()` at exit by design (fixed in Version2). Both logger versions
  write a `log.txt` in the working directory.
- **Long-running:** `06_semaphore`, `05_barrier`, `01_thread/07_jthread`, and the atomic
  increment samples sleep for several seconds.
- `09_coroutines/generator` is interactive (press Enter per value) and needs C++23 `<generator>`.
