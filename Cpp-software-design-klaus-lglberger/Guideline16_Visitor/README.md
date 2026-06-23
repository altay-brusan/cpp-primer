# Guideline 16 — Use Visitor to Extend Operations

> **Concern:** Object-oriented programming makes adding **types** easy but adding
> **operations** hard — every new operation is a new virtual function scattered
> across the whole hierarchy, which violates the Open-Closed Principle (OCP) and
> often is not even possible (you may not be allowed to edit the base class). The
> classic (GoF) **Visitor** design pattern inverts this: over a *closed* set of
> types it keeps the **operation** axis open, so new operations are added as new
> code without modifying the existing types.

## The idea

The book returns to the *draw a shape* scenario: a `Shape` base with a closed set
of concrete shapes (`Circle`, `Square`). We expect an **open set of operations** —
draw, then serialize, rotate, translate, written by people who cannot touch our
code. With plain virtual functions each operation must be added to the base and
re-implemented in every shape: an invasive, OCP-violating change.

Visitor extracts "operations" as a variation point (the Single-Responsibility
Principle acting as an enabler for the OCP):

- A `ShapeVisitor` base declares one pure `visit()` overload per concrete shape.
  Each **concrete visitor is one operation** (`Draw`, `Serialize`, `Area`).
- `Shape` gains a single virtual `accept(ShapeVisitor const&)`. Each shape
  implements it identically as `v.visit(*this)`, but because `*this` has a
  different concrete type per shape it selects a different `visit()` overload.

That is **double dispatch**: `accept()` resolves the *shape* type, `visit()`
resolves the *operation* type. Adding an operation is now one new visitor — no
edit to any shape. The price is symmetric: adding a **type** now forces a new
`visit()` into the base and into every existing visitor (the book calls this the
**Cyclic Visitor**, because the two hierarchies depend on each other).

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_Problem_AddingOperations` | A `Shape` hierarchy with virtual `draw`/`area`. Each operation appears in the base AND in every shape; a third operation (`serialize`) would scatter the same way (shown in comments). The pain of adding operations in OOP. Compiles and runs. |
| 02 | `02_Solution_ClassicVisitor` | The GoF Visitor: an abstract `ShapeVisitor` with `visit(Circle&)`/`visit(Square&)`, and `accept()` on each shape (double dispatch). `Draw`, `Serialize`, and `Area` are added as visitors without touching any shape. Comments call out the trade-off: adding a type now touches every visitor. |

Each sample's `main()` exercises all three shapes and prints results; the
comments explicitly call out which axis is easy and which is hard.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 16

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 16
```

Each sample is a single self-contained `main.cpp` using the standard library
only; no external dependencies.

## Notes

Visitor trades one axis of the OCP for the other:

| | Open axis (easy) | Closed axis (hard) |
|---|---|---|
| Plain virtual functions | add **types** | add **operations** |
| Classic Visitor | add **operations** | add **types** |

- **Pro:** new operations are one new visitor, modifying no existing type — the
  OCP for operations. The logic for one operation also lives in one class
  instead of being scattered across the hierarchy.
- **Con — hard to add types.** A new `Triangle` forces a new pure
  `visit(Triangle&)` into `ShapeVisitor` that every existing visitor must
  implement (a cyclic dependency between the two hierarchies).
- **Con — intrusive.** `accept()` must be added to the base class; if that is
  impossible, classic Visitor is not an option.
- **Con — boilerplate and inflexible.** Every `visit()` overload must exist even
  when the logic is identical (e.g. `Translate`), and the return type is fixed by
  the base, so results are usually stored in the visitor (see `Area`).
- **Con — performance.** Two virtual calls per operation (double dispatch), plus
  the usual per-object allocations and indirections, make it comparatively slow.
- **Con — complexity.** The interplay of two hierarchies is famously hard to
  fully understand and maintain.
- If you forget to override `accept()` in a further-derived shape, the visitor
  silently applies to the wrong type; declaring shapes `final` avoids this but
  blocks future extension.

## Related

→ Guideline 15 (Addition of Types or Operations) frames the either-or choice
Visitor commits to. → Guideline 17 (Consider `std::variant` for Implementing
Visitor) gives a nonintrusive, value-based, faster alternative. → Guideline 5
(Design for Extension) introduces the OCP this pattern serves.
