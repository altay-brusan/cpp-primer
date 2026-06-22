# Chapter 23 — Random Number Facilities

> **Topic:** Generating good-quality random numbers with the `<random>` library —
> engines, engine adapters, and distributions — and why they replace the old
> C-style `rand()`/`srand()`.

## Samples

All samples live in `01_Random`:

| # | File | What it demonstrates |
|---|------|----------------------|
| 01 | `01_old.cpp` | Pre-C++11 `srand()`/`rand()` and why its modulo/low-bit behavior is poor. |
| 02 | `02_random_device.cpp` | `std::random_device` as an entropy source; `entropy()`, `min()`, `max()`. |
| 03 | `03_basic.cpp` | The core recipe: seed an `mt19937` engine, shape output with `uniform_int_distribution`. |
| 04 | `04_basic_time_fallback.cpp` | Seeding from `random_device` with a time-based fallback when entropy is 0. |
| 05 | `05_generate.cpp` | Binding engine+distribution into a generator and filling a vector with `ranges::generate`. |
| 06 | `06_generate_function.cpp` | Passing a bound generator to a helper using abbreviated function-template syntax. |
| 07 | `07_uniform_int_distribution.cpp` | Histogramming 1,000,000 uniform samples to `res.csv`. |
| 08 | `08_normal_distribution.cpp` | The same histogram for a `normal_distribution` (bell curve). |

## Build & run

```powershell
./run.ps1 -Chapter 23           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 23   # compile-check every sample (no run)
```

## Notes

- `07_uniform_int_distribution` and `08_normal_distribution` produce **no console
  output** — they run 1,000,000 iterations and write a `res.csv` (gitignored) in the
  working directory.
- Requires C++20 (`<print>`, ranges, abbreviated templates).
