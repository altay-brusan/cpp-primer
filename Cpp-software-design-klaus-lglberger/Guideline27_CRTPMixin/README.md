# Guideline 27 — Use CRTP for Static Mixin Classes

> **Concern:** CRTP has two distinct roles. As a *design* pattern (Guideline 26)
> it represents an abstraction accessed through a base — a role C++20 concepts
> have largely taken over. As an *implementation* pattern it is a **static mixin**:
> a base class template injects ready-made operations into a derived value type at
> compile time, with no virtual dispatch and no runtime cost. In this second role
> CRTP is *unchallenged* — concepts can constrain a type but cannot synthesize
> operators for it — which is why CRTP is still very much worth knowing today.

## The idea

The book motivates this with a **strong type**. A `StrongType<T, Tag>` wraps a
plain `T` to create a unique, named type — `Meter`, `Kilometer`, `Surname` — so
unrelated values cannot be combined by accident. A bare strong type is
deliberately barren: even `m1 + m2` for two `Meter`s will not compile, because no
operators are inherited from the wrapped `T`. That safety is exactly the point,
but it is too strict — adding two `Meter`s is natural and should yield a `Meter`.

Writing an addition operator per strong type (`Meter`, `Kilometer`, `Mile`, …)
would duplicate identical code, a **DRY** violation. Hoisting one addition
operator into `StrongType` itself would over-correct: now *every* strong type,
including `Surname`, becomes addable. What we actually want is to add operations
**selectively**. That is what CRTP mixins deliver:

- Each operation is a tiny CRTP base class template — a **skill** — parameterized
  on the `Derived` strong type: `Addable<Derived>`, `Comparable<Derived>`,
  `Printable<Derived>`, `Swappable<Derived>`. Each contributes its operators as
  **hidden friends**, injected into the namespace and found by ADL.
- `StrongType` takes a **variadic template-template pack** of skills and derives
  *privately* from each one:
  `struct StrongType : private Skills<StrongType<T,Tag,Skills...>>... {}`.
  Each strong type lists only the skills it wants.
- Operators can be **synthesized**: `Comparable` defines `operator==` and derives
  `operator!=` from it, so a derived type writes neither by hand.

Why this is an *implementation* pattern and not a *design* pattern: the mixin
bases are **private**, have **no virtual (or protected) destructor**, and are
never used through a base pointer. They are pure implementation detail — technical
convenience and DRY, not abstraction — so no polymorphic machinery is required.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_CRTP_Mixin` | A `StrongType<T, Tag, Skills...>` wrapper plus four CRTP skill mixins (`Addable`, `Comparable`, `Printable`, `Swappable`). `Meter` and `Kilometer` reuse all four and stay distinct types; `Surname` reuses everything *except* `Addable`. `main()` exercises the synthesized operators, and `static_assert`s prove that `Meter` is addable, `Surname` is not, and `Meter + Kilometer` never compiles. |

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 27

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 27
```

The sample is a single self-contained `main.cpp` using the standard library only.

## Notes

- **Why this CRTP use remains valuable.** C++20 concepts replaced CRTP as a *design*
  pattern (static type categories), but a concept only *checks* a type — it cannot
  *add* members or operators to it. Mixing in operations at compile time is still
  uniquely CRTP territory, so the mixin form stays in the C++ toolbox.
- **The strong-type idea.** Wrapping a `T` behind a distinct `Tag` produces a type
  with semantic meaning (`Meter`, not "some `long`"). Accidental cross-domain
  arithmetic (`Meter + Kilometer`, `Surname + Surname`) simply fails to compile,
  closing the door on a whole class of bugs at no runtime cost.
- **Skills are opt-in.** The variadic pack lets each strong type pick exactly the
  operations it needs. `Surname` is printable, comparable, and swappable, but not
  addable — concatenating two surnames is meaningless, so the skill is omitted.
- **Synthesis kills boilerplate.** A mixin can derive related operators from a
  primitive one (`operator!=` from `operator==`, binary `operator+` from the
  combined-assignment form), so each derived type implements neither.
- **Implementation pattern, not design pattern.** Private bases, no virtual
  destructor, never accessed polymorphically: the inheritance here buys technical
  elegance, not abstraction. That is the distinction Guideline 27 asks you to make.

## Related

→ Guideline 26 (CRTP for Static Type Categories) is CRTP in its *design-pattern*
role, the contrast this guideline draws. → Guideline 20 (Favor Composition over
Inheritance) explains why the inheritance here is acceptable: it is private,
non-polymorphic implementation detail. → Guideline 22 (Prefer Value Semantics)
frames why strong value types are worth building.
