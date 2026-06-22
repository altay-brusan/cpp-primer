# Chapter 17 — Understanding Iterators and the Ranges Library

> **Topic:** Iterators as the glue between containers and algorithms — iterator
> categories and traits, stream and adapter iterators — and the C++20/23 Ranges
> library: views, range adapters, factories, projections, and lazy pipelines.

## Samples

| # | Folder | What it demonstrates |
|---|--------|----------------------|
| 01 | `01_IteratorTraits` | `iterator_traits<Iter>::value_type` to name the type an iterator refers to. |
| 02 | `02_Iterators` | Basic iterator looping (`cbegin`/`cend`) and generic `myPrint()`/`myFind()` over `[begin, end)`. |
| 03 | `03_Advance` | Reimplementing `advance()` via classic tag dispatching, then C++20 concept-constrained overloads. |
| 04 | `04_StreamIterators` | `ostream_iterator`, `istream_iterator`, and `istreambuf_iterator`. |
| 05 | `05_IteratorAdaptors` | `back_insert_iterator`, `insert_iterator`, `reverse_iterator` (with `base()`), `move_iterator`. |
| 06 | `06_Ranges` | Range algorithms/projections, views & adapters, lazy `\|` pipelines, modifying through a view, factories (`iota`, `repeat`), `istream_view`, and `ranges::to`. |

## Build & run

```powershell
./run.ps1 -Chapter 17           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 17   # compile-check every sample (no run)
```

## Notes

- **Wait for keyboard input:** `04_StreamIterators/02_istream_iterator`,
  `06_Ranges/09_istream_view`.
- **Need a data file:** `04_StreamIterators/03_istreambuf_iterator` reads
  `some_data.txt` from the working directory (exits 1 if absent).
- **Require C++23:** `06_Ranges/02_views` (`views::zip`, `adjacent`, `chunk`,
  `stride`, `enumerate`, `cartesian_product`), `06_Ranges/08_repeat_view`
  (`views::repeat`), `06_Ranges/10_range_conversions` (`ranges::to`, `from_range`).
