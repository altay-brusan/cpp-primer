# Guideline 31 — Use External Polymorphism for Nonintrusive Runtime Polymorphism

> **Concern:** Strategy (Guideline 19) and its value-based form (Guideline 23)
> isolated *how* a shape is drawn, but the shapes were still forced to carry a
> `draw()` member and inherit from a `Shape` base. Drawing is an isolated aspect:
> shapes should be *oblivious* to the fact that they can be drawn. The **External
> Polymorphism** design pattern extracts the **entire polymorphic behavior** out
> of the types into a separate, external hierarchy — so unrelated, nonpolymorphic
> types can be treated polymorphically without ever opting into a base class.

## The idea

The book returns to the 2D-graphics example. With Strategy, `Circle` still
inherited from `Shape` and still had to implement `draw()`. External Polymorphism
removes the `Shape` base class entirely:

- **The shapes become plain value types.** `Circle` and `Square` have **no base
  class and not a single virtual function**. They are reduced to geometric
  primitives that know nothing about drawing, rotating, serialization, or any
  graphics library — no artificial dependency at all.
- **A separate, external hierarchy carries the behavior.** An abstract
  `ShapeConcept` declares the polymorphic operations (here just `draw()`); it
  takes the place of the old `Shape` base. A `ShapeModel<T>` **class template**
  is the *only* class that ever inherits from `ShapeConcept`. It stores a `T` by
  composition (Guideline 20) and implements the virtual `draw()` by **delegating**
  to an injected strategy — never implementing the detail itself.
- **Intent** (Cleeland, Schmidt, Harrison, 1996): *allow C++ classes unrelated by
  inheritance and/or having no virtual methods to be treated polymorphically.*
- **Combines runtime and compile-time polymorphism.** `ShapeConcept` is the
  runtime abstraction over all types; the `ShapeModel<T>` template generates the
  shape-specific code. The strategy can be a runtime `std::function` *or* a
  compile-time template policy with a `DefaultDrawer` default that simply calls a
  free `draw()` — which inverts the dependency and imposes no member-function
  requirement on the type.
- **External Polymorphism vs. Adapter.** Adapter standardizes a type to an
  *existing* interface; External Polymorphism creates a *new* external hierarchy
  to treat a set of existing, nonpolymorphic types polymorphically.
- **The one shortcoming.** It is not a value-based solution: user code must still
  explicitly instantiate `ShapeModel` and juggle `unique_ptr`s. Guideline 32
  (Type Erasure) packages exactly this machinery behind a clean value type.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_ExternalPolymorphism` | The core pattern. Plain `Circle`/`Square` value types with no base and no virtual functions; an abstract `ShapeConcept` plus a `ShapeModel<T, DrawStrategy>` template that stores a `T` and forwards `draw()` to an injected `std::function`. A `vector<unique_ptr<ShapeConcept>>` is drawn polymorphically — the shapes never knew they were drawable. |
| 02 | `02_CompileTimePolicy` | The strategy as a *template* parameter with a `DefaultDrawer` default that calls a free `draw()`. Demonstrates the book's most striking point: any type — even a built-in `int` — gains polymorphic behavior nonintrusively, simply because a free `draw(int)` exists. |

Each sample is one self-contained `main.cpp` whose `main()` builds the external
models and draws them; drawing backends are simulated with console output.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 31

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 31
```

Each sample uses the standard library only (`<memory>`, `<vector>`,
`<functional>`).

## Notes

- **Behavior is decoupled from the types.** The polymorphic operations live in
  `ShapeConcept`/`ShapeModel`, not in `Circle`/`Square`. The value types carry no
  dependency on graphics libraries, base classes, or virtual functions — a very
  loose coupling that beautifully serves the SRP and DIP.
- **Nonintrusive extension (OCP).** Adding a new kind of shape — even a
  third-party type you cannot edit — needs no inheritance and no Adapter: just
  instantiate `ShapeModel` for it. The inheritance boilerplate is written once,
  in the wrapper (DRY).
- **One concept, two strategy flavors.** A runtime `std::function` (sample 01) is
  flexible and storable; a compile-time template policy (sample 02) removes the
  indirection for speed and keeps the choice in exactly one place. Prefer
  building on a *free* function to invert the dependency.
- **A proper abstraction still matters.** `ShapeConcept` is subject to the ISP
  and LSP like any base class: the `int`-as-shape trick compiles, but whether it
  *should* is a question of choosing the right abstraction (perhaps `Drawable`).
- **Gateway to Type Erasure.** This external Concept/Model hierarchy is the exact
  foundation of Guideline 32: Type Erasure wraps these pointers and virtual calls
  inside a copyable value type, keeping the decoupling while removing the manual
  allocations and the leaked `unique_ptr`s from user code.

## Related

→ Guideline 19 (Strategy) and Guideline 23 (Value-Based Strategy) extracted *how*
a shape is drawn; this extracts the *whole* polymorphic behavior. → Guideline 20
(Composition over Inheritance) is why `ShapeModel` *stores* a shape. →
Guideline 24 (Adapters) is the close cousin to contrast against. → Guideline 32
(Type Erasure) builds directly on this pattern.
