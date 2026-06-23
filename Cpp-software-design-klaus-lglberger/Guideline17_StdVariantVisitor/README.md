# Guideline 17 — Consider std::variant for Implementing Visitor

> **Concern:** The classic Gang-of-Four Visitor solves the right problem (keep
> the set of operations open) but pays for it with heavy machinery: a `Shape`
> base class, an `accept` hook, a `Visitor` base class, virtual `visit`
> functions, owning pointers, and a cyclic dependency between the abstraction and
> its alternatives. A **value-based** Visitor built on `std::variant` and
> `std::visit` keeps the same architectural property with none of that
> boilerplate.

## The idea

`std::variant<Circle, Square, ...>` is a **sum type**: it holds exactly one of a
closed set of alternatives and is always type-safe and properly initialized.
Used as the abstraction over "some shape," it lets us drop everything the classic
Visitor needed:

- **No base classes.** `Circle` and `Square` become plain value types. There is
  no `Shape` base class for them to derive from and no `Visitor` base class to
  satisfy.
- **No `accept` hook.** The design is *nonintrusive* — the shapes know nothing
  about being visited, so the style can even be added to types you do not own.
- **No pointers, no allocation.** Variants are values, so they live directly in a
  `std::vector<Shape>`. The only reason the classic version reached for
  `std::unique_ptr` was heterogeneous storage; the variant supplies that.
- **An operation is just a callable.** Any object that provides one `operator()`
  per alternative works; `std::visit` performs the type dispatch. Adding an
  operation is a new visitor that modifies nothing, so the **Open-Closed
  Principle** still holds for operations.

The contract is loose — "one `operator()` per alternative" — and each operation
chooses its own return type. The book also notes a real architectural win: unlike
the classic Visitor, there is **no cyclic dependency** between the variant and
its alternatives, so you can even form new variant abstractions on the fly (for
example a `RoundShapes` variant) without touching the shape classes.

The price is the mirror image of the classic Visitor: the **type set is closed**.
Adding a new alternative means editing the variant alias and every visitor — but
a missing `operator()` is a **compile error**, not a silent fall-through.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_Solution_VariantVisit` | The recommended value-based Visitor: `std::variant<Circle, Square>` stored in a `std::vector`. `Draw` is a hand-written struct visitor (one `operator()` per type); `area` fuses lambdas with the `overload` helper. A second operation is added by writing a second visitor, nothing else. |
| 02 | `02_Compare_ClassicVisitor` | The same draw-and-area behavior in the intrusive Gang-of-Four style — `Shape` base, `ShapeVisitor` base, `accept`, virtual `visit`, and `std::unique_ptr` storage — to make the boilerplate and indirection concrete. |

Each sample is a single self-contained `main.cpp` using the standard library
only, and each `main()` prints its results.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 17

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 17
```

## Notes

- **`overload` helper.** `struct overload : Ts... { using Ts::operator()...; };`
  plus the deduction guide `overload(Ts...) -> overload<Ts...>;` is the standard
  trick to build a visitor from a set of lambdas. It compiles on MSVC with
  C++20 and later, so it is used directly in sample 01.
- **Trade-off vs. classic Visitor.** Both keep the operation set open. The
  value-based version wins on boilerplate, value semantics, the absence of a
  cyclic dependency, and performance (the book benchmarks the classic Visitor as
  the slowest measured approach, due to double dispatch). The classic version's
  one advantage is an open *type* axis: a new shape is a new derived class with
  no central edit.
- **Shortcomings to respect (from the book).** The variant's type set is closed,
  so a new alternative ripples into the alias and every visitor; avoid mixing
  alternatives of very different sizes (the variant is sized for the largest);
  and the alternative types are visible through the variant, which can create
  physical (recompilation) dependencies. Hiding them behind a pointer, Proxy, or
  Bridge restores encapsulation at some performance cost.
- **`std::get_if` alternative.** `std::visit` is the clean dispatch; the book
  notes a manual `std::get_if` chain can be faster but is a maintenance hazard,
  so it is mentioned only, not used here.

## Related

→ Guideline 16 (Use Visitor to Extend Operations) introduces the classic form.
→ Guideline 15 (Addition of Types or Operations) frames the open-operations vs.
open-types choice this guideline lives inside.
→ Guideline 18 (Beware the Performance of Acyclic Visitor) continues the
performance discussion.
