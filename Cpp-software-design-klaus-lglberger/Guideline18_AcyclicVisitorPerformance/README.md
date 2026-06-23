# Guideline 18 — Beware the Performance of Acyclic Visitor

> **Concern:** The **Acyclic Visitor** is a clever variation of the Visitor
> pattern that breaks the *cyclic dependency* of the classic (GoF) Visitor, so
> you can keep **both** the type axis and the operation axis open at runtime —
> the thing Guideline 15 said was usually impractical. The catch is *why* it is
> impractical: every visitation goes through a `dynamic_cast` **cross-cast**,
> which the book measures at roughly an **order of magnitude** slower than a
> cyclic Visitor. Understand the architectural win; respect the runtime cost.

## The idea

The classic Visitor has a cycle among its key players: the single `Visitor`
base class lists one `visit` overload **per concrete shape** (`visit(Circle)`,
`visit(Square)`, …), the shapes depend on `Shape`, and `Shape` depends on
`Visitor`. That cycle pins every player onto one architectural level, so adding
a new **type** forces an edit to the shared `Visitor` base and recompiles
everything. Visitor keeps the *operation* axis open but locks the *type* axis.

The Acyclic Visitor breaks the cycle by **splitting** the visitor base:

- **`AbstractVisitor`** — an *empty* base with only a virtual destructor. It is
  a polymorphic **tag**; it names no shape, so it depends on nothing below it.
- **`Visitor<T>`** — one tiny per-type interface produced by a class template. A
  concrete operation inherits `AbstractVisitor` **plus** a `Visitor<Shape>` for
  each shape it chooses to support.

Now no high-level type names a concrete shape, so **both** new types and new
operations are additive. Each shape's `accept(const AbstractVisitor&)` recovers
its specific interface with a `dynamic_cast`:

```cpp
void accept(const AbstractVisitor& v) const override
{
    if (const auto* cv = dynamic_cast<const Visitor<Circle>*>(&v))
        cv->visit(*this);
}
```

In the sample, `Triangle` is added **without touching** `AbstractVisitor`,
`Circle`, or `Square` — proof that the cyclic dependency is gone.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_AcyclicVisitor` | An empty `AbstractVisitor` tag, templated `Visitor<T>` interfaces, and shapes whose `accept()` does a `dynamic_cast` cross-cast. Adds a `Triangle` **type** with zero edits to shared code, then times many `dynamic_cast` visitations against the same work done by a direct virtual call. |

`main()` first draws every shape through the visitor, then runs a small
`<chrono>` benchmark: the `dynamic_cast` path versus a plain virtual `area()`
call. Both compute the same sum (printed so the optimizer keeps the work), and
the cross-cast path comes out visibly slower.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 18

# Verify the sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 18
```

The sample is a single self-contained `main.cpp` using the standard library
only (`<chrono>` is included explicitly for the timing block).

## Notes

The Acyclic Visitor is an inversion of the usual Visitor trade-off:

| Property | Cyclic (GoF) Visitor | Acyclic Visitor |
|----------|----------------------|-----------------|
| Add a new **operation** | easy (one new visitor) | easy (one new visitor) |
| Add a new **type** | invasive (edit shared `Visitor` base) | easy (no shared edit) |
| Dispatch cost | one virtual call | `dynamic_cast` cross-cast **plus** virtual call |

- **Why the cast is so slow.** It is not a downcast. `AbstractVisitor` and
  `Visitor<Circle>` are *sibling* bases of the concrete visitor, so recovering
  one from the other is a **cross-cast** — RTTI must walk sideways through the
  multiple-inheritance hierarchy. A cross-cast followed by a virtual call is
  much costlier than a single virtual dispatch. The book reports the Acyclic
  Visitor at almost an order of magnitude over the cyclic Visitor.
- **The cast is architecturally safe here.** A `dynamic_cast` is dangerous when
  high-level code reaches *down* into low-level types. Here both the shapes and
  the visitors live on the low level, so no architectural boundary is violated —
  only performance suffers.
- **`AbstractVisitor` must be polymorphic.** Its virtual destructor is what lets
  `dynamic_cast` probe it; the empty body is intentional — it carries no
  operation, just identity.
- **Decision rule.** Reach for the Acyclic Visitor only when you genuinely need
  both axes open at runtime *and* the visitation is not on a hot path. Otherwise
  a cyclic Visitor, an `std::variant`-based visitor (Guideline 17), or an
  object-oriented design (Guideline 15) will be far faster.

## Related

→ Guideline 15 (Design for the Addition of Types or Operations) frames the
either-or that the Acyclic Visitor tries to escape. → Guideline 16 (Use Visitor
to Extend Operations) is the cyclic Visitor this one rebalances. → Guideline 17
(Consider `std::variant` for Implementing Visitor) is the fast, value-based
alternative the book benchmarks against.
