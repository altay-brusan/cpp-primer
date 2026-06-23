# Guideline 26 — Use CRTP to Introduce Static Type Categories

> **Concern:** A family of related types (a linear-algebra library's
> `DynamicVector` and `StaticVector`) shares an interface — `size`, subscript,
> `begin`/`end` — and shares free functions like the output operator and
> `l2norm`. We want **one abstraction** for that family without duplicating code.
> A runtime base class would impose a **virtual call on every element access**,
> which is unacceptable in performance-critical contexts (HPC, games, HFT). The
> **CRTP** gives the same abstraction as a **compile-time** relationship, with no
> virtual dispatch. With C++20, a **concept** often supersedes this use of CRTP.

## The idea

The book wants a *new type category* — a set of "dense vector" types that the
output operator and `l2norm` accept, and nothing else. A fully generic
`template<typename T>` operator accepts *everything* (`int`, `std::string`, …),
violating Core Guideline T.10; a virtual base class makes element access pay for
a vtable. Both are wrong.

**CRTP** keeps the base-class idea but makes the base a *class template*:

```cpp
template <typename Derived>
struct DenseVector {
    Derived& derived() { return static_cast<Derived&>(*this); }
    std::size_t size() const { return derived().size(); }
    decltype(auto) operator[](std::size_t i) { return derived()[i]; }
    // ...
};

template <typename T>
class DynamicVector : public DenseVector<DynamicVector<T>> { /* ... */ };
```

The base names the **derived type as its own template parameter**, so it can
`static_cast` to the derived type and **forward** every call — a compile-time
relationship, not a runtime one. The cast typically inlines to nothing.

Key mechanics the book stresses:

- **`decltype(auto)` return types.** The base cannot read the derived nested
  types (the derived class is still *incomplete* when the base is instantiated),
  and a `ZeroVector` may return elements **by value**. `decltype(auto)` forwards
  exactly what the derived returns, staying correct as the family grows.
- **Members instantiated on demand.** The base *can* call derived member
  functions because member functions of a class template are only instantiated
  when used — by then the derived type is complete.
- **Protected nonvirtual destructor** (Core Guideline C.35): there is no runtime
  polymorphism, so no virtual destructor and no deletion through a base pointer.
- **Free functions become templates** on `Derived` — a real cost (template code
  spreads, definitions move to headers).

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_CRTP_StaticInterface` | A CRTP base `DenseVector<Derived>` forwards `size`, subscript, and `begin`/`end` to the derived type via `static_cast`. `DynamicVector` (heap), `StaticVector` (in-class array), and `ZeroVector` (by-value, motivating `decltype(auto)`) all share one static interface; the free `operator<<` and `l2norm` serve the whole category — with **no virtual calls**. |
| 02 | `02_Concept_Alternative` | The same static category as a **C++20 concept**, refined by a customizable `IsDenseVector` trait so it is *specific* (rejects `std::vector`). Membership is **non-intrusive**: `DynamicVector` opts in via a private `DenseVectorTag` base; `StaticVector` opts in via a trait **specialization** with no edit to the class. `static_assert`s prove the boundary. |

Each sample is a single self-contained `main.cpp` using the standard library
only; `main()` exercises the static interface and prints the results.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 26

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 26
```

## Notes

- **CRTP vs concepts.** They express the *same* idea — a compile-time abstraction
  for a family of types. The book's guidance: **prefer the C++20 concept when you
  can**, because it is *non-intrusive*. A type need not derive from anything; it
  can even join the category from the outside via a trait specialization, which
  CRTP cannot do for foreign code.
- **Specificity needs an opt-in.** A purely structural concept ("has `size` and
  subscript") also matches `std::vector` and `std::string`. Refine it with an
  explicit marker (`DenseVectorTag`) routed through a customizable trait
  (`IsDenseVector`), applying the SRP so structural requirements and membership
  are separate concerns. Then the concept truly supersedes CRTP.
- **What CRTP still offers.** A concept gives **no shared implementation**: each
  type writes its own members. A CRTP base *can* hold common code. So CRTP earns
  its keep when the base provides reusable behavior (see Guideline 27, CRTP for
  static mixins), not merely a category tag.
- **CRTP's drawbacks (book).** No common base class — `DynamicVector` and
  `StaticVector` have *different* base instantiations, so they cannot share a
  polymorphic container; everything touching the base becomes a template; CRTP is
  intrusive; and it is compile-time only — no runtime polymorphism.
- **No silver bullet.** CRTP is not a replacement for every inheritance
  hierarchy. Use it (or a concept) only when a *static* type abstraction is what
  you need.

## Related

→ Guideline 7 (Base Classes and Concepts) frames the base-class/concept duality
this guideline exploits. → Guideline 24 (Adapters) is the fallback when a type
cannot intrusively opt in. → Guideline 27 (CRTP for Static Mixins) is CRTP's
other major use — sharing *implementation*, where concepts do not replace it.
→ Guideline 36 (Runtime vs Compile-Time Abstraction) weighs the broader
trade-off.
