# Guideline 29 — Be Aware of Bridge Performance Gains and Losses

> **Concern:** The Bridge/Pimpl indirection is not free — an extra pointer hop, a
> heap allocation, and worse cache locality can make code **slower**. But the same
> tool can make code **faster**: a *partial* Bridge keeps frequently-used ("hot")
> data inline and pushes only rarely-used ("cold") data behind the pointer,
> shrinking the object so hot loops stream through fewer cache lines. Either way,
> the answer is the same: **measure, do not guess.**

## The idea

Guideline 28 builds a Bridge to remove physical dependencies. Guideline 29 asks
the honest follow-up: *what does that indirection cost?* The book benchmarks one
logical `Person` (six strings plus a year of birth) in three layouts and, over a
large vector, repeatedly finds the oldest person with `std::min_element`. Only the
**memory layout** changes:

- **`PersonInline` (no Bridge).** All seven members live inline. On a 64-bit
  machine this is ~150–200 bytes. The baseline.
- **`PersonFullPimpl` (full Pimpl idiom).** Every member moves behind a
  `unique_ptr`, so the object is only 8 bytes — but reading the year now hops to a
  scattered heap block on every access. The book measures this at **~11% slower
  (GCC) / ~13% slower (Clang)** than the inline baseline: the indirection penalty.
- **`PersonPartial` (partial Bridge).** Hot data (`forename`, `surname`, `year`)
  stays inline; cold data (the postal address) moves into `Impl`. The object drops
  to roughly half the inline size (~64–80 bytes). The book measures this at
  **~14% faster (GCC) / ~6.5% faster (Clang)** than the baseline.

Why does shrinking help? The operation *looks* compute-bound (compare integers)
but is actually **memory-bound**. Memory is loaded in 64-byte cache lines, and the
inline layout uses only a few percent of every line it pulls in — almost all the
loaded bytes are unused. A smaller object means a smaller stride, so the hot loop
wastes far less bandwidth. There is a whole spectrum between "all inline" and "all
hidden"; you choose, per case, where hiding implementation detail should yield to
inlining the hot members.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_BridgePerformance` | Times the same "find the oldest person" hot loop over three layouts of one `Person` — (a) all data inline, (b) full Pimpl, (c) partial Bridge — and prints object sizes and timings. The full Pimpl should run slower than inline (indirection); the partial Bridge should run faster (smaller hot object, better locality). Uses `<chrono>` and the standard library only. |

`main()` builds all three vectors from the same fixed seed (identical data, only
the layout differs), times each, and prints the ratios against the inline
baseline. A `volatile`-sourced bias is added to both sides of the comparator so
the optimizer cannot hoist the repeated `min_element` out of the loop.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 29

# Verify the sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 29
```

The sample is a single self-contained `main.cpp` using the standard library only.
Exact numbers depend on your CPU, caches, and build; run it a few times and
compare the **ratios**, not the absolute milliseconds. Release-mode optimization
is where the locality effect shows up most clearly.

## Notes

- **A Bridge generally costs performance.** Indirection, a heap block, lost
  inlining, and worse locality add up. The full-Pimpl layout in the benchmark is
  measurably slower than plain inline data. Do not assume the abstraction is free.
- **A partial Bridge can gain performance.** Separate frequently-used data from
  rarely-used data, keep the hot members inline, and push the cold members behind
  the pointer. The smaller object improves cache behavior on hot loops — the book
  records a clear speedup over the all-inline layout.
- **It is a dichotomy, and it depends.** Inlining hot members runs *against* the
  Bridge's goal of hiding implementation details. There is no rule; you decide
  case by case which aspect to favor, and there is a full range of solutions
  between the two extremes.
- **Smaller types help elsewhere, too.** Reducing a type's size can make it a
  viable alternative in `std::variant` (Guideline 17), not just faster in loops.
- **Measure, do not guess.** Every number depends on element count, member sizes,
  the machine, and the computation. Confirm a suspected bottleneck — or a
  suspected improvement — with a representative benchmark on real code and data.

## Related

→ Guideline 28 (Build Bridges to Remove Physical Dependencies) introduces the
Bridge this guideline benchmarks. → Guideline 17 (Consider `std::variant` for
Implementing Visitor) benefits from the smaller types a Bridge can produce.
→ Guideline 22 (Prefer Value Semantics over Reference Semantics) shares the theme
that indirection and allocation have real, measurable costs.
