# Chapter 22 — Date and Time Utilities

> **Topic:** The `<ratio>` and `<chrono>` libraries — compile-time rational
> numbers, durations, clocks, time points, the C++20 calendar types, and time
> zones.

## Samples

| # | Folder | What it demonstrates |
|---|--------|----------------------|
| 01 | `01_Ratio` | Compile-time rational arithmetic/comparison with `std::ratio`, `ratio_add`, `ratio_less`. |
| 02 | `02_Chrono/01_durations` | Custom & predefined `duration` types, arithmetic, and `duration_cast`. |
| 02 | `02_Chrono/02_now` | Current UTC time via `system_clock::now()` and locale-aware chrono formatting. |
| 02 | `02_Chrono/03_timing` | Timing a block with the monotonic `steady_clock`. |
| 02 | `02_Chrono/04_time_point` | `time_point` basics: epoch, adding durations, `time_since_epoch()`. |
| 02 | `02_Chrono/05_time_point_conversions` | Changing precision via `time_point_cast`. |
| 02 | `02_Chrono/06_dates` | C++20 calendar types (`year`/`month`/`day`, `year_month_day`, weekday helpers). |
| 02 | `02_Chrono/07_time_zones` | C++20 tz database, `locate_zone`/`current_zone`, `zoned_time`. |

## Build & run

```powershell
./run.ps1 -Chapter 22           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 22   # compile-check every sample (no run)
```

## Notes

- Requires a C++20+ toolchain; `06_dates` and `07_time_zones` need a standard library
  shipping the IANA time-zone database (recent MSVC/libstdc++ do).
- `02_now`, `06_dates`, `07_time_zones` print wall-clock/locale-dependent output that
  varies by run/machine. `07_time_zones` expects named zones/locales (e.g.
  `America/New_York`, `nl-NL`) to be available.
