# Chapter 20 — Mastering Standard Library Algorithms

> **Topic:** Practical use of the `<algorithm>` and `<numeric>` generic
> algorithms — searching, comparing, counting, modifying, partitioning,
> sorting, binary search, set operations, min/max, parallel execution, numeric
> reductions, and the C++20/23 constrained `ranges::` versions.

## Samples

| # | Folder | What it demonstrates |
|---|--------|----------------------|
| 01 | `01_AlgorithmOverview` | `find`/`find_if` with function-pointer/functor/lambda predicates, `accumulate`, and the `std::ref` callback-copy issue. |
| 02 | `02_NonModifyingAlgorithms` | Search variants, the Boyer-Moore searcher, comparison algorithms, and counting (`all_of`/`any_of`/`none_of`, `count_if`). |
| 03 | `03_ModifyingAlgorithms` | `generate`, `transform`, `copy`/`move` family, `replace_if`, `erase_if`, the remove-erase idiom, `shuffle`, `sample`, `reverse`, `shift_left/right`. |
| 04 | `04_OperationalAlgorithms` | `for_each` (basic, accumulating, in-place) and `for_each_n`. |
| 05 | `05_PartitionAlgorithms` | `partition_copy` and `partition`. |
| 06 | `06_SortingAlgorithms` | `sort` with a comparator and `nth_element`. |
| 07 | `07_BinarySearchAlgorithms` | `lower_bound` and `binary_search` on sorted ranges. |
| 08 | `08_SetAlgorithms` | `includes`, the `set_union`/`intersection`/`difference`/`symmetric_difference` ops, and `merge`. |
| 09 | `09_MinMaxAlgorithms` | `min`/`max`/`minmax`/`minmax_element` and `clamp`. |
| 10 | `10_ParallelAlgorithms` | `sort` with an `execution::par` policy. |
| 11 | `11_NumericalAlgorithms` | `iota`, `reduce` (vs `accumulate`), and `inner_product`. |
| 12 | `12_ConstrainedAlgorithms` | C++20/23 `ranges::` versions, the boolean `contains`/`starts_with`, and `fold_left_first`/`fold_right_last`. |

## Build & run

```powershell
./run.ps1 -Chapter 20           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 20   # compile-check every sample (no run)
```

## Notes

- **Wait for keyboard input** (many samples fill a container from `cin`): most of
  `01_AlgorithmOverview/*`, plus `02/03_ComparisonAlgorithms`, several
  `03_ModifyingAlgorithms/*`, `04/02`–`04/03`, `05/*`, `06/*`, `07/*`, `08/*`, and
  `10_ParallelAlgorithms`. Type values, then the end-of-input signal the sample asks for.
- Some samples use recent features: `01/03_FindIfFunctor` (C++23 `static operator()`),
  `10`/`11/02_reduce` (`<execution>` policies), `12/04`–`12/05` (C++23 `ranges::contains`,
  `fold_*`).
