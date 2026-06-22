# Chapter 16 — Overview of the C++ Standard Library

> **Topic:** A guided tour of what the Standard Library offers — containers,
> iterators, algorithms, smart pointers, numerics, and small but handy
> vocabulary/utility pieces — so you know what's available before diving deep
> in later chapters.

## Samples

| # | Folder | What it demonstrates |
|---|--------|----------------------|
| 01 | `01_cmp_greater` | C++20 safe mixed-sign integer comparison `std::cmp_greater` (`<utility>`), vs. a naive `(-1 > 0u)` that wrongly yields `true`. |
| 02 | `02_bit` | C++20 `<bit>` utilities (`popcount`, `countl_one`/`countr_one`, `rotl`, `bit_ceil`/`bit_floor`) plus C++23 `std::byteswap`. |
| 03 | `03_FeatureTestMacros` | Probing library support at compile time via `<version>` and the `__cpp_lib_constexpr_vector` feature-test macro. |

## Build & run

```powershell
./run.ps1 -Chapter 16           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 16   # compile-check every sample (no run)
```

## Notes

- Requires a modern toolchain: `std::println` (`<print>`) and `cmp_*`/`<bit>` are
  C++20; `std::byteswap` is C++23.
- `03_FeatureTestMacros` prints different (valid) output depending on whether the
  library defines `__cpp_lib_constexpr_vector` — expected, not an error.
