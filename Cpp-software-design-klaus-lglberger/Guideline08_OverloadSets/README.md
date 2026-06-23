# Guideline 8 — Understand the Semantic Requirements of Overload Sets

> **Concern:** A set of identically named **free functions** (an *overload set*
> like `std::swap`, `std::begin`/`std::end`, `std::size`) is a powerful
> **compile-time abstraction** and a **customization point**: any type can join
> it nonintrusively, and generic code selects the right overload through
> **argument dependent lookup (ADL)**. But — exactly like a base class or a
> concept — an overload set carries **semantic requirements** (the LSP). If you
> join the set, you must honor its expected meaning, or generic code that trusts
> the set silently does the wrong thing.

## The idea

Next to concepts, function overloading via free functions is C++'s second
compile-time abstraction mechanism. From a set of identically named functions
the compiler picks one based on the argument types — an **overload set**. It has
two faces, and the guideline is about respecting both.

- **The power (a customization point).** You can add a free function to *any*
  type — `int`, `std::string`, a third-party type — without modifying it. That
  is the **Open-Closed Principle**: extend by adding code, not by editing it. The
  book's `traverseRange()` shows why this matters: written against *member*
  `begin()`/`end()` it artificially excludes the built-in array; rewritten on the
  *free* `begin()`/`end()` overload set it becomes truly generic. The Standard
  Library is built on exactly this idea (`std::swap`, `std::begin`, `std::size`).
- **The problem (semantic expectations).** All that power only works if every
  overload in the set behaves as the set promises. The book's `Widget::swap`
  that swaps only half the object compiles fine, is chosen by ADL, and then
  betrays every caller. *Joining an overload set subjects you to its expected
  behavior — the LSP applies to overload sets too.* Hence Core Guidelines C.162
  ("overload operations that are roughly equivalent") and C.163 ("overload *only*
  for operations that are roughly equivalent").

The enabling mechanism — and the thing every sample demonstrates — is the
canonical **two-step calling convention**:

```cpp
using std::swap;   // make the generic version visible as a fallback...
swap(a, b);        // ...call unqualified so ADL can prefer a custom overload
```

Qualifying the call (`std::swap(a,b)`) defeats the customization point; dropping
the `using` declaration breaks types that rely on the standard version.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_Problem_BrokenSwap` | A custom `swap(Widget&,Widget&)` joins the swap overload set but swaps only `i`, not `j`. It compiles, ADL selects it, and a generic helper silently half-swaps the object — an LSP violation *at the overload-set level*. Compiles and runs. |
| 02 | `02_Solution_ProperSwap` | The same `swap()` fixed to exchange the full state, plus the two-step `using std::swap; swap(a,b);` convention. The unchanged generic helper now works for `Widget` (via ADL) **and** `int` (via the `std::swap` fallback). |
| 03 | `03_Customization_BeginEnd` | The constructive side: a generic `sumRange()` built on the **free** `begin()`/`end()` overload set serves a built-in array, a `std::vector`, and a custom `Trio` that plugs in by adding two free functions — no edits to existing code. |

Each sample's `main()` exercises more than one type so the abstraction is
concrete, and prints its results.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 8

# Verify every sample compiles (MSVC, /std:c++latest /W4):
./run.ps1 -Verify -Guideline 8
```

Each sample is a single self-contained `main.cpp` using the standard library
only.

## Notes

- The broken-overload bug is **silent**: it compiles cleanly under `/W4`, ADL
  selects it, and only the wrong runtime value reveals the violation. One
  non-conforming overload poisons every generic algorithm that trusts the set.
- Be aware of the existing overload sets (`std::swap`, `std::begin`,
  `std::cbegin`, `std::end`, `std::cend`, `std::data`, `std::size`) and of
  naming conventions: `find()` implies a linear search, `begin()`/`end()` must
  yield iterators (not start/stop a process). The name sets the expectation.
- Free functions also separate concerns (SRP) and promote reuse (DRY): they have
  no implicit `this`, so the operation becomes an isolated, reusable service —
  the design philosophy behind the STL's container/iterator/algorithm split.

## Related

→ Guideline 6 (Adhere to the Expected Behavior of Abstractions) introduces the
LSP for abstractions; → Guideline 7 extends it to concepts; this guideline
extends it to overload sets. → Guideline 5 (Design for Extension) uses the same
`std::swap`-style overload set as a compile-time extension point.
