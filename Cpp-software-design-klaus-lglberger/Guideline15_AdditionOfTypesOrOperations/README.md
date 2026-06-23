# Guideline 15 — Design for the Addition of Types or Operations

> **Concern:** Dynamic polymorphism is not the unlimited freedom it sounds
> like — it forces a choice. There are **two axes of extensibility**: adding
> new **types** and adding new **operations**. This is the **expression
> problem**. With dynamic polymorphism you can keep only *one* axis open; you
> must decide, up front, which way your code will grow.

## The idea

The book returns to the *draw a shape* scenario. Two designs solve it, and they
are mirror images of each other on the two axes of the Open-Closed Principle
(OCP):

- **Object-oriented (dynamic polymorphism).** A `Shape` base class fixes a
  **closed set of operations** (virtual `draw`, `area`). Adding a new **type**
  is one new derived class — trivial, nothing else recompiles. But adding a new
  **operation** (say `serialize`) means editing the base class *and* every
  derived class. **Types open, operations closed.**
- **Procedural / functional.** A `std::variant<Circle, Square, Triangle>` fixes
  a **closed set of types**, and operations are free visitors applied with
  `std::visit`. Adding a new **operation** is one new visitor — trivial, nothing
  else changes. But adding a new **type** means editing the variant *and* every
  visitor. **Operations open, types closed.**

The procedural side has a bonus: with a closed `variant`, a forgotten case is a
**compile error**, not the silent fall-through of the enum-plus-switch from
Guideline 5.

Choose by expectation: if you will mostly add **types**, prefer the OO solution;
if you will mostly add **operations**, prefer the procedural/functional one.
(The book notes that *static* polymorphism can keep both axes open, and that two
truly open axes at runtime — the Acyclic Visitor — is possible but usually
impractical for performance reasons.)

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_OO_DynamicPolymorphism` | `Shape` base with virtual `draw`/`area`. Adding a `Triangle` **type** is one new class (easy); adding a `serialize` **operation** would touch the base and every class (hard, shown in comments). |
| 02 | `02_Procedural_Variant` | `std::variant<Circle, Square, Triangle>` plus `std::visit` visitors. Adding a `serialize` **operation** is one new visitor (easy); adding a `Pentagon` **type** would touch the variant and every visitor (hard, shown in comments). |

Each sample's `main()` exercises all three shapes and prints results; the
comments explicitly call out which axis is easy and which is hard.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 15

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 15
```

Each sample is a single self-contained `main.cpp` using the standard library
only (`std::variant` and `std::visit` are part of it).

## Notes

The two designs are an inversion of each other on the OCP's two dimensions:

| Paradigm | Strength (open axis) | Weakness (closed axis) |
|----------|----------------------|------------------------|
| Object-oriented (virtual functions) | Addition of **types** | Addition of **operations** |
| Procedural / functional (variant plus visit) | Addition of **operations** | Addition of **types** |

- Exploit the strength of the paradigm you pick; do not ignore its weakness, or
  you walk into a maintenance trap.
- Adding to the **closed** axis is the invasive change — it forces edits to
  existing, working code (the OCP violation). Both samples keep that direction
  in comments so the cost is explicit but the file still compiles.
- `static` polymorphism (templates) is not bound by this either-or: both axes
  are visible at compile time and can be extended. Runtime is where you must
  choose.

## Related

→ Guideline 5 (Design for Extension) introduces the OCP and the
enum-plus-switch problem that the procedural design here fixes with a `variant`.
→ Guideline 16 (Use Visitor to Extend Operations) builds directly on this:
Visitor is the pattern for keeping the **operation** axis open over a closed set
of types. → Guideline 17 (Consider `std::variant` for Implementing Visitor)
turns sample 02 into the recommended modern form.
