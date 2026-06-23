# Guideline 36 — Understand the Trade-off Between Runtime and Compile Time Abstraction

> **Concern:** Guideline 35 showed the Decorator pattern only in its classic,
> pointer-to-base, object-oriented form. But the same design can be realized at
> **either end of the abstraction spectrum**: at **runtime** (dynamic
> polymorphism — flexible, composable while the program runs, but paying for
> indirection and heap allocations) or at **compile time** (static polymorphism —
> zero overhead and fully inlinable, but frozen at build time, with longer builds
> and weaker encapsulation). This guideline weighs the two using Decorator as the
> running example, and both solutions are firmly **value-based** (Guideline 22).

## The idea

The book takes the priced-item Decorator (a `ConferenceTicket` wrapped in
`Discounted` and `Taxed` price modifiers) and implements it twice, on almost
opposite sides of the design space:

- **Compile time, with templates.** The decoration stack becomes part of the
  **type**: `Taxed<0.15, Discounted<0.2, ConferenceTicket>>`. A C++20 concept,
  `PricedItem`, takes the role of the old `Item` base class — it states the
  requirement (a `price()` member) every decorated type must meet. `Discounted`
  decorates by composition (Guideline 20), `Taxed` by private inheritance; both
  are valid. Rates are non-type template parameters, so each distinct rate is a
  distinct type. No base class, no virtual call, no allocation — the compiler
  inlines the whole `price()` computation. The book measures this at roughly
  **8% of the runtime** of the classic Decorator: faster by more than an order
  of magnitude.
- **Runtime, with Type Erasure.** A single value type `Item` (Guideline 32) wraps
  any priced thing behind a hidden `Concept`/`Model` hierarchy. `Discounted` and
  `Taxed` become plain value types that simply **own an `Item`** and forward
  `price()` to it — perfect Decorators with no visible pointers. Because every
  decoration shares the one static type `Item`, wildly different stacks can live
  together in one container and even be assembled from user input at run time.
  The book measures this at essentially the **same speed** as the classic
  runtime Decorator (about 1.0).
- **Neither is "the" answer.** The compile-time approach dominates on performance
  but loses all runtime flexibility and pushes implementation into headers
  (wider recompiles, leaked detail). The runtime approach is flexible and hides
  details well but cannot inline across layers. Real designs usually sit
  somewhere between the two extremes.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_Runtime_Decorator` | The **runtime** Decorator. A value-based Type-Erasure `Item` wraps any priced type; `Discounted`/`Taxed` own an `Item` and forward `price()`. Stacks are composed, stored in one `vector<Item>`, and one layer is even chosen *while running*. Cost: one heap allocation plus one virtual call per layer. |
| 02 | `02_CompileTime_Decorator` | The **compile-time** Decorator. The stack is the *type*: `Taxed<0.15, Discounted<0.2, ConferenceTicket>>`, guarded by a `PricedItem` concept. No virtual calls, no allocations, fully inlinable — but every rate combination is a new type fixed at build time and each stack needs its own container. |

Each sample is one self-contained `main.cpp` whose `main()` builds and prices the
decoration stacks; both produce the same `459.08` for a 20% discount then 15% tax.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 36

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 36
```

Each sample uses the standard library only — sample 01 needs `<memory>` for the
Type-Erasure `unique_ptr`; sample 02 needs `<concepts>` for the `PricedItem`
constraint.

## Notes

Runtime versus compile-time abstraction, as the book frames it:

| Aspect | Runtime (Type Erasure, sample 01) | Compile time (templates, sample 02) |
|--------|-----------------------------------|-------------------------------------|
| Abstraction mechanism | Dynamic polymorphism (virtual `Concept`) | Static polymorphism (`PricedItem` concept) |
| Decoration stack is… | **data** — built/decided at run time | **a type** — fixed at compile time |
| Performance | indirection + heap per layer (~1.0) | inlinable, zero overhead (~0.08) |
| Runtime flexibility | high — compose from user input | none — frozen at build time |
| One container for mixed stacks | yes (`vector<Item>`) | no — one container per type |
| Encapsulation / build cost | details hide in source, local recompiles | templates in headers, wider recompiles |
| Code size | small, fixed | grows per rate combination |

- **Both are value-based.** No `new`/`delete` in user code, natural copy
  semantics — the book's preferred direction (Guideline 22) over the classic
  reference-semantics Decorator.
- **The concept mirrors the base class.** `PricedItem` (compile time) and the
  erased `Concept` (runtime) play the same role the `Item` base played in the
  classic pattern: they own the abstraction and serve the OCP and DIP.
- **Pick by what you know.** Use the compile-time form when all decorations are
  known at build time and performance is critical; use the runtime form when
  decorations must vary, be stored together, or stay hidden behind a stable
  interface. Most real code blends the two.

## Related

→ Guideline 35 (Decorator) introduces the pattern this guideline re-implements. →
Guideline 32/33 (Type Erasure) is the machinery behind the runtime sample. →
Guideline 20 (Composition over Inheritance) and Guideline 22 (Value Semantics)
underpin both. → Guideline 29 (Bridge performance) makes the same
runtime-vs-compile-time trade-off in a different setting.
