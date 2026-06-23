# Guideline 6 — Adhere to the Expected Behavior of Abstractions

> **Concern:** An abstraction is not just an interface — it is a set of
> **requirements and expectations**. Decoupled code depends on the *expected
> behavior* of an abstraction, so every subtype must honor it. The **Liskov
> Substitution Principle (LSP)** captures this: an IS-A relationship is about
> *behavior*, not inheritance or mathematics. If a subtype cannot keep the
> base's promises, it is not a true subtype.

## The idea

The book uses the classic Rectangle / Square example. A `Rectangle` base class
owns two side lengths and makes an implicit but real promise: you can set the
width and the height **independently** — setting one must not change the other.
A `Square` then publicly inherits from `Rectangle`, because "a square is a
rectangle" geometrically. But a square has only *one* side length, so to keep
its own invariant (all sides equal) it must override `setWidth` and `setHeight`
to change *both* members. By protecting its own invariant, the `Square` breaks
the independence promise of the base.

A `transform()` function that depends only on the `Rectangle` abstraction sets
the width to 7 and the height to 4 and expects an area of 28. For a real
rectangle the expectation holds; for a square the second setter overwrites the
first, so the area is 16. The book's version asserts and the process aborts.
The expectation in the abstraction was **violated** — an LSP violation. The
inheritance compiles, but it does **not** express a true IS-A relationship: a
`Square` cannot be used everywhere a `Rectangle` is expected.

The fix is to stop forcing an IS-A relationship that does not hold behaviorally:

- **Model the behavior honestly (no false IS-A).** Introduce an abstraction that
  promises only what every subtype can truly deliver (here, a `Shape` that
  promises only `area()`). Keep the independent-sides behavior on `Rectangle`
  alone, give `Square` its own single-side interface, and do **not** derive one
  from the other. Functions that need independent sides ask for a `Rectangle`,
  so passing a `Square` is impossible — the misuse is caught by the compiler, not
  discovered at run time.
- **Honor the contract in any hierarchy you do keep.** The LSP spells out the
  rules of behavioral subtyping: a subtype must not **strengthen preconditions**,
  must not **weaken postconditions**, and must **preserve the base's
  invariants** (return types may be covariant; parameters contravariant). A
  hierarchy that follows these rules is a genuine IS-A and is always safe to
  substitute.

And, as the book stresses: communicate the expectations of an abstraction
clearly — in self-documenting code first, and in documentation where needed. The
C++ standard's iterator concepts (with explicit pre- and postconditions) are the
model to follow.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_Problem_LSPViolation` | The classic violation: `Square` inherits from `Rectangle` and overrides the setters to keep its sides equal, breaking the independence promise. `transform()` expects area 28 but gets 16. Compiles and runs; prints the broken expectation instead of aborting. |
| 02 | `02_Solution_NoInheritance` | Honest modeling: a minimal `Shape` abstraction promises only `area()`; `Rectangle` and `Square` are separate `Shape`s. The independent-sides behavior lives on `Rectangle` alone, so `transform(Rectangle&)` cannot be handed a `Square` — the compiler prevents the misuse. |
| 03 | `03_Solution_Contract` | The general rule: a `Discount` abstraction with a documented precondition and postcondition, and two subtypes that honor it exactly (no strengthened precondition, no weakened postcondition). A genuine IS-A — every subtype is safely substitutable. |

Each sample's `main()` prints whether the abstraction's expectation was honored
or broken, so the difference between the LSP violation and the corrected designs
is visible at run time.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 6

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 6
```

Each sample is a single self-contained `main.cpp` using the standard library
only.

## Notes

- **Geometry is not behavior.** A square is a rectangle in mathematics, but the
  LSP IS-A relationship depends on the actual interface and its expectations. As
  long as `setWidth` and `setHeight` are independent, a `Square` will always
  violate them.
- **Inheritance is a hard feature, not an intuitive one.** Whenever you use it,
  ensure every expectation of the base class is fulfilled by the derived type.
- **Do not "fix" violations with `dynamic_cast` workarounds.** Special-casing a
  misbehaving subtype (`if (dynamic_cast<Special*>(&b)) ...`) makes calling code
  depend on the (mis)behavior of derived types. The book calls this very bad
  practice and still an LSP violation.
- **A base class is still a valid abstraction.** Calling code can and should
  depend only on the expected behavior of the abstraction. That dependency is
  exactly what makes an LSP violation a programming error.
- **Choose meaningful abstractions and communicate them.** Robust, decoupled
  software requires abstractions we can count on — backed by self-documenting
  code and, where needed, documented pre- and postconditions.

## Related

→ Guideline 2 (Design for Change) and Guideline 5 (Design for Extension) rely on
abstractions that calling code can depend on; this guideline says those
abstractions must be *behaviorally* trustworthy.
→ Guideline 7 (Similarities Between Base Classes and Concepts) extends the same
expectation-honoring idea to compile-time abstractions.
