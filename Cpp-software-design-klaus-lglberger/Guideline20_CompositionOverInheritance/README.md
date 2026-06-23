# Guideline 20 — Favor Composition over Inheritance

> **Concern:** Inheritance is the strongest, most rigid form of coupling, and it
> is routinely overused. When two things vary independently, modeling *both* with
> inheritance fuses them and explodes the class count. **Composition** —
> *has-a* instead of *is-a* — lets the dimensions vary on their own. As the book
> puts it: *"Delegate to services: has-a trumps is-a."*

## The idea

The book makes a careful, deliberately mild case against inheritance. It is not
bad — used properly it is powerful — but it is *hard* to use properly, so it is
both misused (the LSP failures of Guideline 6) and overused. Two points matter:

- **Inheritance is not reuse.** You do not reuse the base class by inheriting it;
  you become reusable *by code that uses the base class polymorphically*. Real
  reuse comes from the polymorphic *use* of a type, not from polymorphic types.
- **Inheritance creates coupling.** A base class fixes your function signatures,
  return types, and structure. The Strategy discussion showed this: an
  inheritance-based variation forced a deeper hierarchy and impaired reuse.

The takeaway the book wants you to carry into the rest of the patterns: *many
design patterns are enabled by **composition**, not inheritance.* Strategy works
not because strategies inherit a base class, but because a class **aggregates a
data member** (the strategy) and **delegates** to it.

This folder makes the cost concrete with two varying dimensions — **what** we
draw (Circle, Square, …) and **how** we draw it (Console, OpenGL, SVG):

- **Both dimensions as inheritance → a class per combination.** `CircleConsole`,
  `CircleOpenGL`, `SquareConsole`, `SquareOpenGL`, … The count is **M times N**,
  behavior is duplicated, and the dimensions are tangled.
- **One dimension composed in → addition, not multiplication.** A `Shape` *has-a*
  `DrawBackend` and delegates rendering to it. Now it is **M plus N**: a new
  backend works with every shape, and a new shape works with every backend.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_Problem_InheritanceExplosion` | Both dimensions modeled with inheritance: `CircleConsole`, `CircleOpenGL`, `SquareConsole`, `SquareOpenGL`. 2 shapes by 2 backends already needs 4 leaf classes; the formatting and the geometry members are duplicated. Growth is M times N. Compiles and runs. |
| 02 | `02_Solution_Composition` | A `Shape` *has-a* `DrawBackend` and delegates to it. Backends are shape-agnostic; shapes are backend-agnostic. A new `Triangle` works with every backend and a new `SvgBackend` works with every shape — no edits to the other dimension. Growth is M plus N. |

Each sample's `main()` exercises several combinations so the difference between
multiplying and adding the dimensions is visible in the output.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 20

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 20
```

Each sample is a single self-contained `main.cpp` using the standard library
only; the rendering backends are small std-based stubs that print to `std::cout`.

## Notes

- **M times N versus M plus N.** Fusing both dimensions with inheritance makes
  the class count *multiplicative*: every new shape must be paired with every
  backend, and vice versa. Composing one dimension in makes it *additive*: the
  shape and backend hierarchies grow separately and combine at runtime.
- **Inheritance is rarely the answer.** The book does not forbid inheritance —
  the `Shape` hierarchy in sample 02 is still inheritance, and it is fine, because
  it only enables *polymorphic use*. The behavior that *varies* (the backend) is
  composed in, not inherited. That is how Strategy, and many patterns, are built.
- **Reuse comes from delegation, not derivation.** In sample 02 the Console
  formatting lives in exactly one place and is reused by every shape; in sample
  01 it is copied into every `*Console` leaf class.
- Keep inheritance for the one dimension that genuinely needs runtime
  polymorphism; reach for composition for everything that varies alongside it.

## Related

→ Guideline 19 (Strategy) is the pattern this composition realizes — isolate
*how* a thing is done behind an injected service.
→ Guideline 6 (Expected Behavior / LSP) covers the *subtle* failures of
inheritance that make composition the safer default.
→ Guideline 2 (Design for Change) and Guideline 5 (Design for Extension) explain
why decoupling the varying dimensions is what keeps software adaptable.
