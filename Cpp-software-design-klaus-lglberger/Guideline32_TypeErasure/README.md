# Guideline 32 — Consider Replacing Inheritance Hierarchies with Type Erasure

> **Concern:** An inheritance hierarchy forces every participating type to *buy
> in* (inherit a base, supply virtual functions) and pushes you into
> reference semantics — base-class pointers, manual allocations, manual lifetime.
> **Type Erasure** keeps the strong decoupling of External Polymorphism but wraps
> it in a single, regular **value type** (`Shape`) that can hold *any* type
> satisfying an implicit interface, with no inheritance on the concrete types and
> full value semantics (copy, move, store in a `std::vector`).

## The idea

Type Erasure is not a brand-new technique but a **compound design pattern** — a
clever combination of three patterns the book has already built up:

- **External Polymorphism** supplies the decoupling and the nonintrusive nature:
  an abstract `ShapeConcept` and a templated model live *outside* the concrete
  shapes, so `Circle` and `Square` remain plain, unrelated, nonpolymorphic
  structs that never inherit and never declare a virtual function.
- **Bridge** supplies the value-based implementation: the wrapper stores a
  `unique_ptr<ShapeConcept>` (a pimpl). The concrete type hides behind that
  pointer-to-base, and the wrapper itself has *no* template parameter.
- **Prototype** supplies copy semantics: `ShapeConcept` exposes a `clone()`, so
  the wrapper can deep-copy whatever it owns without ever knowing the real type.

The result is the intent stated in the book: *"Provide a value-based,
nonintrusive abstraction for an extendable set of unrelated, potentially
nonpolymorphic types with the same semantic behavior."* After the templated
constructor runs, `Shape` keeps only a pointer-to-base — its memory of the
concrete type has been **erased**, hence the name.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_TypeErasure_Shape` | A `Shape` value type. Templated ctor `Shape(T)` erases `T` into a heap `ShapeModel<T>`; an internal abstract `ShapeConcept` declares `do_draw()` + `clone()`; the model forwards `do_draw()` to a free `draw(const T&)`; a copy ctor deep-copies via `clone()`; a hidden-friend `draw(const Shape&)` forwards through the bridge. `Circle`/`Square` are plain structs with their own free `draw()`, **no base class**. `main()` fills a `std::vector<Shape>`, copies the whole container by value, reassigns one element, and proves the original is untouched. |

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 32

# Verify the sample compiles (MSVC, /std:c++latest, /W4):
./run.ps1 -Verify -Guideline 32
```

The sample is a single self-contained `main.cpp` using the standard library only
(`<memory>`, `<vector>`, `<utility>`, plus `<concepts>`/`<type_traits>` for the
constraint). Drawing is simulated with console output.

## Notes

- **Concept / Model / Bridge structure.** `ShapeConcept` is the abstract base
  (the requirement set): `do_draw()` and `clone()`. `ShapeModel<T>` is the *one*
  template that implements it — it stores a `T` by value, implements `do_draw()`
  by calling the free `draw(const T&)` (found by argument-dependent lookup), and
  implements `clone()` by copying itself into a fresh model. `Shape` holds a
  single `unique_ptr<ShapeConcept>`: the Bridge that hides the concrete type.
- **Why it gives value semantics.** The bridge member is a `unique_ptr`, so the
  destructor and both move operations are correct by default. Copying is the only
  hard part, and `clone()` (Prototype) solves it: the copy constructor deep-copies
  the owned object *without knowing its type*. The whole external hierarchy —
  pointers, allocations, lifetime — is encapsulated inside `Shape`, so callers see
  only a plain, copyable, movable value.
- **Nonintrusive and extendable.** The concrete types do not inherit anything and
  carry no virtual functions; they are connected to drawing only through a free
  function. Adding a new shape is a new struct plus a free `draw()` for it — no
  edit to `Shape`, `ShapeConcept`, or `ShapeModel`.
- **The templated-ctor trap.** `template<class T> Shape(T)` is greedy and could
  out-match `Shape(const Shape&)`, hijacking the copy. The `requires`-clause
  (`!std::same_as<remove_cvref_t<T>, Shape>`) excludes `Shape`, so the real copy
  constructor wins for `Shape` arguments.
- **Known limitations.** Type Erasure excels at **unary** operations but is
  awkward for **binary** ones: equality comparison of two `Shape`s is not
  straightforward (it needs a `dynamic_cast` or similar and answers the loaded
  question "when are two shapes equal?"). The other cost is implementation
  complexity — a basic wrapper is roughly 30 lines, but performance and
  exception-safety details get tricky fast.

## Related

→ Guideline 31 (External Polymorphism) is the reference-semantics ancestor this
pattern upgrades. → Guideline 28 (Bridge) supplies the pimpl; Guideline 30
(Prototype) supplies `clone()`. → Guideline 33 (Optimization Potential of Type
Erasure) removes the allocations with the Small Buffer Optimization. →
Guideline 22 (Value Semantics) is the philosophy this pattern delivers.
