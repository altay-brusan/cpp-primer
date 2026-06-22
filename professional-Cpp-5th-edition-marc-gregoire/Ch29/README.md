# Chapter 29 — Writing Efficient C++

> **Topic:** Performance — language-level efficiency (pass-by-reference vs value,
> move, `std::unreachable`), design-level efficiency (object pools), and
> profiler-driven optimization.

## Samples

| # | Folder | What it demonstrates |
|---|--------|----------------------|
| 01 | `01_Person` | Pass-by-value vs pass-by-reference, counting copies/destructions via a chatty `Person`. |
| 02 | `02_UnreachableCode` | `std::unreachable()` in a `switch` default to inform the optimizer. |
| 03 | `03_ObjectPool` | A header-only `ObjectPool<T>` plus a benchmark vs `make_unique` for 500,000 objects. |
| 04 | `04_NameDB` | The same baby-name database optimized in three passes: `vector` linear scan → `std::map` (O(log n)) → a streamlined `++m_names[name]`. |

## Build & run

```powershell
./run.ps1 -Chapter 29           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 29   # compile-check every sample (no run)
```

## Notes

- **Benchmarks** (`03_ObjectPool/ObjectPoolTest`, the `04_NameDB` attempts) are meant
  to be built in **release/optimized** mode and are long-running; the debug build that
  `run.ps1` produces will be much slower.
- **Data file:** the `04_NameDB` samples read `boys_long.txt` (~500k lines, provided in
  `04_NameDB/`). The programs look for it in the current working directory — run them
  from the folder that contains `boys_long.txt` (or copy it next to the executable).
- `01_Person` and `02_UnreachableCode` are simple standalone programs.
