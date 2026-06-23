# Guideline 34 — Be Aware of the Setup Costs of Owning Type Erasure Wrappers

> **Concern:** An **owning** Type Erasure wrapper (the `Shape` of Guideline 32)
> has value semantics: converting a `Circle` into a `Shape` **copies** the
> erased object and its strategy and performs a **heap allocation** inside
> `make_unique`. Used merely as a function parameter, it pays that copy plus
> allocation on every call — the same trap `std::function` falls into. When you
> only need to *operate* on an object that already exists, a **non-owning**
> type-erased view (a pointer to the object plus a dispatch function pointer, no
> copy, no allocation) is far cheaper.

## The idea

In Guideline 32 the `Shape` wrapper stores a *copy* of the concrete shape behind
a `unique_ptr`. That is exactly what makes it a well-behaved value — but it means
that passing a stack `Circle` to a `void use(Shape const&)` builds a temporary
`Shape`, which:

1. invokes the non-explicit, templated `Shape` constructor;
2. **copies** the shape (cheap for `Circle`, possibly expensive otherwise) and
   the draw strategy;
3. **allocates** a model on the heap inside `make_unique` (definitely expensive).

The book stresses this is *not* specific to `Shape`: `std::function` behaves the
same way, because it too is an *owning* abstraction that performs a deep copy.
The contrast is `std::string_view` and `std::span` — *non-owning* abstractions
that are cheap to copy because they hold only a pointer (and a size). They are
shallow, so they are ideal as function parameters.

The remedy is a **simple non-owning Type Erasure** wrapper, the book's
`ShapeConstRef`. It stores three things and nothing more:

- a `void const*` to the existing shape,
- a `void const*` to the existing draw strategy,
- a function pointer that performs the manually implemented virtual dispatch
  (the optimization technique from Guideline 33).

No allocation, no deep copy — constructing it is just a few pointer stores, and
the object is trivially copyable. Its constructor takes **lvalue references**, so
rvalues (temporaries) cannot bind, which heads off the most obvious dangling
mistakes. It still must not outlive what it points to.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_NonOwningView` | A lightweight non-owning `ShapeConstRef` (object pointer plus strategy pointer plus a dispatch function pointer) draws stack `Circle`/`Square` objects with **zero** allocations, contrasted against the owning `Shape` whose every setup copies and heap-allocates. A global `operator new` counter and a `chrono` loop quantify the gap. |

The single `main.cpp` builds an owning `Shape` and a non-owning `ShapeConstRef`
from the same stack `Circle`, draws through both, reports how many heap
allocations each setup needed, and times 100,000 setups of each.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 34

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 34
```

The sample is a single self-contained `main.cpp` using the standard library
only; drawing is simulated with console output and a replaced global
`operator new`/`operator delete` counts heap allocations.

## Notes

- **Owning wrapper setup cost.** Value semantics mean the wrapper always copies
  the erased object and always owns the copy. Construction therefore pays a copy
  of the shape, a copy of the strategy, and one heap allocation — every time.
  `std::function` shares this cost; it is an owning abstraction.
- **Non-owning view cost.** `ShapeConstRef` performs only a shallow copy: it
  stores pointers, so construction and copying are essentially free. It is the
  Type Erasure equivalent of `std::string_view` and `std::span`.
- **Reference-semantics deficiencies.** The non-owning form pulls you back into
  reference semantics: it does **not** own its target and must not outlive it.
  Taking arguments by lvalue reference (rejecting rvalues) gives reasonable but
  not total protection against dangling.
- **When each fits.** Prefer the non-owning view for **function arguments** —
  the place where the cheap, span-like behavior matters most. Use the owning
  wrapper when you must **store** the abstraction (a data member) or **return**
  it, where ownership and lifetime safety are required.
- **Keep it simple.** The simple non-owning implementation shown here is usually
  enough. The book also describes a more powerful variant (in-class `std::byte`
  storage plus a `NonOwningShapeModel` and `clone`-into-memory) that interacts
  efficiently with the owning `Shape` and supports a real deep copy when copied
  into an owning wrapper — at the cost of more machinery. Reach for it only when
  the extra indirections of the simple form actually hurt.

## Related

→ Guideline 32 (Replace Inheritance Hierarchies with Type Erasure) introduces
the owning `Shape` wrapper this guideline measures. → Guideline 33 (Optimization
Potential of Type Erasure) supplies the manual virtual dispatch and small-buffer
techniques the non-owning view reuses. → Guideline 22 (Prefer Value Semantics)
explains why the owning wrapper copies in the first place.
