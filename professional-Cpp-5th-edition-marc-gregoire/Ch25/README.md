# Chapter 25 — Customizing and Extending the Standard Library

> **Topic:** Building your own Standard-Library-compatible pieces — using/writing
> allocators, writing generic algorithms, and building a custom container with
> hand-written iterators.

## Samples

| # | Folder | What it demonstrates |
|---|--------|----------------------|
| 01 | `01_allocator` | Using `std::allocator` directly: separating allocate/deallocate from object lifetime (placement `new` + `std::destroy_at`). |
| 02 | `02_WritingAlgorithms` | Writing a custom `find_all()` algorithm — a concept-constrained version and a modernized Ranges-style version with a sentinel and projection. |
| 03 | `03_DirectedGraphBasic` | A first minimal custom container (directed graph) with no iterators yet, plus a DOT exporter. |
| 04 | `04_DirectedGraph` | The full Standard-Library-compatible container with hand-written const iterators (node and adjacent-node iterators) and all the required type aliases. |

## Build & run

```powershell
./run.ps1 -Chapter 25           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 25   # compile-check every sample (no run)
```

## Notes

- `03`/`04` are header-only templates compiled via their folder's `test.cpp` driver.
- **Compiler note:** both `directed_graph_to_dot.h` files add `#include <ostream>` so the
  `std::println(std::ostream&, …)` overloads are visible — the newest MSVC moved those
  overloads into `<ostream>` (the book relied on `<print>` pulling them in).
