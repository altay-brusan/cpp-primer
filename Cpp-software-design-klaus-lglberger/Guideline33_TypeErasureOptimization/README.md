# Guideline 33 — Be Aware of the Optimization Potential of Type Erasure

> **Concern:** The basic Type Erasure wrapper from Guideline 32 is already fast,
> but it leaves performance on the table: it **heap-allocates unconditionally**
> (slow, nondeterministic, sometimes unavailable) and **dispatches through
> virtual calls** (two indirections each). Because Type Erasure gives us a *value
> type and a wrapper* — not just a pointer-to-base — we are in full control of
> memory and dispatch, and can optimize both.

## The idea

This guideline is the book's one detour into pure performance. It takes the
unoptimized Type Erasure `Shape` wrapper and shows two independent optimizations.

- **Small Buffer Optimization (SBO).** Instead of always calling
  `std::make_unique`, give the wrapper an aligned in-class byte buffer and
  construct the erased *model* **in place** with `std::construct_at` (placement
  new) when it fits. Small objects then incur **no heap allocation** at all;
  large objects fall back to the heap. The wrapper now owns the model's lifetime
  directly: `std::construct_at` to build, a `clone`/`move` into the destination
  buffer to copy/move, and `std::destroy_at` to run the (virtual) destructor.
  The standard library uses this trick in `std::function` and `std::any`, though
  the standard never *requires* it. The price: the wrapper becomes a class
  template parameterized on `Capacity` and `Alignment`.
- **Manual virtual dispatch.** A virtual call goes through the per-object `vptr`
  to the type's virtual function table, then through the table to the function —
  two indirections. Replace the virtual functions with a hand-built table of
  **function pointers stored inside the wrapper**: one indirection. Once every
  virtual function (including the destructor) is replaced, the `Concept` base
  disappears and `OwningModel` becomes pure storage. The table entries are
  **stateless lambdas** (which decay to function pointers) created in the
  templated constructor, where the concrete types are still known, so the
  `static_cast` from `void*` back to the real model is type safe.

The book measures both: SBO is roughly 20% faster than the fastest Strategy
form; manual dispatch gives a large win on GCC (and is neutral on Clang).
Combining them does not always beat SBO alone. The deeper point: these wins are
possible **only because we separated virtual behavior into a value type** — a
plain pointer-to-base could never be optimized this way.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_SmallBufferOptimization` | A `Shape<Capacity, Alignment>` wrapper that constructs the erased model inline (`std::construct_at` into an `alignas` buffer) when it fits, and heap-allocates otherwise. An instrumented `operator new` proves small shapes (and their copies) cause **zero** allocations while a large shape falls back to one. |
| 02 | `02_ManualVTable` | A `Shape` wrapper with no `Concept` base: a `unique_ptr<void, DestroyOperation*>` plus `draw_`/`clone_` function pointers form a hand-built dispatch table, initialized from stateless lambdas. Drawing, copying (via `clone_`), and moving (defaulted, pointer stolen) all work through plain function pointers. |

Each sample is a single self-contained `main.cpp` using the standard library
only; drawing backends are simulated with console output.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 33

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 33
```

## Notes

- **SBO trades space for speed.** A fixed inline buffer removes heap traffic and
  fragmentation for the common, small case. The cost is the reserved buffer and
  the fact that the wrapper becomes a class template, which tends to make calling
  code templated too. A compile-time `sizeof`/`alignof` check (here via
  `if constexpr`) selects inline storage only when the model fits and is not
  over-aligned; everything else stays correct on the heap.
- **Manual lifetime management is real work.** With in-class memory the wrapper
  must build with placement new (`std::construct_at`), copy/move the *model*
  (not the bytes) into the destination, and tear down with `std::destroy_at`
  (which runs the virtual destructor). For inline objects there is no `delete`,
  only the destructor call; the buffer is `alignas(Alignment)` so placement new
  into it is well defined.
- **Manual dispatch trades a few pointers for one fewer indirection.** Storing
  the function pointers in the wrapper replaces the `vptr` plus vtable lookup
  with a single direct call, and lets the `Concept` base vanish. The cost is
  extra pointers per wrapper and copy operations you must write by hand (clone
  the model, copy the table).
- **It depends, and you can measure.** The book reports the manual-dispatch win
  is large on GCC and neutral on Clang, and that SBO plus manual dispatch does
  not always beat SBO alone. Profile on your own toolchain before committing.
- **Where the freedom comes from.** None of this is possible with a raw
  pointer-to-base. It is the *value type plus wrapper* of Type Erasure that hands
  you control over memory and dispatch in the first place.

## Related

→ Guideline 32 (Replace Inheritance Hierarchies with Type Erasure) builds the
unoptimized wrapper these optimizations refine. → Guideline 31 (External
Polymorphism) is the inheritance pattern SBO keeps and manual dispatch removes.
→ Guideline 19 (Strategy) supplies the injectable drawing behavior, and the
policy-based storage idea the book suggests for switching memory strategies.
→ Guideline 34 (Setup Costs of Owning Type Erasure Wrappers) continues the
performance discussion.
