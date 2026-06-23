# Guideline 37 — Treat Singleton as an Implementation Pattern, Not a Design Pattern

> **Concern:** Singleton guarantees a class has *exactly one* instance and offers
> a *global point of access* to it. That is useful, but it introduces **no
> abstraction** and **decouples nothing** — so by the book's own definition it is
> an **implementation pattern**, not a design pattern. It is also global mutable
> state, which quietly harms testability and changeability.

## The idea

The book opens by addressing the elephant in the room: *Singleton is not a design
pattern.* Yes, it is one of the 23 original Gang of Four patterns, Wikipedia calls
it a design pattern, and so does *Code Complete*. It nevertheless fails the book's
definition of a design pattern (from Guideline 11), which requires that a pattern:

- has a **name** — Singleton does;
- carries an **intent** — *"ensure a class has only one instance, and provide a
  global point of access to it"* — Singleton does;
- introduces an **abstraction** — Singleton does **not**: no base class, no
  template parameter, nothing;
- has been **proven** — Singleton has (if infamously).

Because Singleton introduces no abstraction, it is not concerned with the
structure, interaction, or interdependencies of entities, and so it does **not aim
at managing or reducing dependencies** — which the book defines as the heart of
software design. Its sole job is to restrict the number of instances to exactly
one. That is an *implementation detail*, hence Singleton is an **implementation
pattern**.

The recommended way to write one is the **Meyers' Singleton**: a `static
instance()` member that returns a reference to a **function-local static**. The
single instance is created the first time control passes through the declaration —
and since C++11 that initialization is **thread-safe** with no manual locking.
Every other construction path is closed: the default constructor is private and
copy/move are deleted, so `instance()` is the only door in.

One subtle detail the book stresses: the default constructor is **written out, not
defaulted**. Up to C++17 a defaulted private constructor leaves the class an
*aggregate*, so `Database db{};` could still create an instance via aggregate
initialization. Providing the constructor removes that loophole.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_MeyersSingleton` | A `Database` written as a Meyers' Singleton: `static instance()` returning a function-local static, private constructor, deleted copy/move. `main()` takes two references, asserts they share one address, writes through one and reads back through the other to prove the single shared state, and notes the C++11 thread-safety guarantee. |

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 37

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 37
```

The sample is a single self-contained `main.cpp` using the standard library only.

## Notes

- **Implementation pattern, not design pattern.** Singleton has a name, an intent,
  and a track record, but it introduces no abstraction and reduces no
  dependencies. It manages an *implementation detail* — the instance count — so it
  belongs with idioms like RAII, not with Strategy or Visitor.
- **Meyers' Singleton is the right implementation.** A function-local static gives
  lazy, once-only, thread-safe (since C++11) construction with no manual locking,
  and a clean global access point through `instance()`.
- **Close every other door.** Private (hand-written, not defaulted) constructor
  plus deleted copy and move guarantee that `instance()` is the only way to obtain
  the object, and that the class is not an aggregate that could be value-
  initialized around the private constructor.
- **The real cost is global state.** A Singleton is global, mutable, and depended
  upon *implicitly*: callers reach for `instance()` directly instead of receiving
  it. That coupling makes code harder to test (no seam to substitute a fake) and
  harder to change. Use Singleton deliberately, only when a class genuinely
  represents something that exists exactly once.

## Related

→ Guideline 11 (Understand the Purpose of Design Patterns) defines what a design
pattern is and introduces the term *implementation pattern*. → Guideline 1
(Importance of Software Design) frames design as managing dependencies, which
Singleton does not do. → Guideline 38 (Design Singletons for Change and
Testability) tackles the global-state downsides head-on.
