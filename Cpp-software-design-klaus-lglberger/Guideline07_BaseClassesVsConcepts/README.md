# Guideline 7 — Understand the Similarities Between Base Classes and Concepts

> **Concern:** A base class with virtual functions and a C++20 concept are two
> sides of the same coin. A base class is a **runtime** abstraction; a concept
> is a **compile-time** abstraction. Both define a set of expected operations
> and behavior — both are *formal descriptions of expected behavior* that
> calling code relies on. The **Liskov Substitution Principle (LSP)** therefore
> applies to static (templated) polymorphism just as it does to dynamic
> (inheritance) polymorphism.

## The idea

The book asks a deceptively simple question: what is the difference between a
`useDocument()` written against a `Document` *base class* and one written
against a `Document` *concept*?

```cpp
// Runtime: works only with classes derived from the Document base class.
void useDocument(Document const& doc);

// Compile-time: works only with types that satisfy the Document concept.
template <Document T> void useDocument(T const& doc);
```

Syntactically they differ (one uses inheritance and a vtable, the other a
constrained template). **Semantically they are the same.** In both cases
`useDocument()` works *only with classes adhering to the expectations of the
`Document` abstraction*. Both the base class and the concept represent a set of
requirements — syntactic *and* semantic — and so both are a formal description
of expected behavior and a way to communicate expectations to calling code.

That is the duality the guideline drives at:

- **Base class = runtime abstraction.** The set of expected operations is the
  set of (pure) virtual functions. Binding is dynamic (vtable). It enables
  heterogeneous collections and binary interface boundaries.
- **Concept = compile-time abstraction.** The set of expected operations is the
  `requires`-clause. Binding is static; there is no vtable and no runtime cost,
  but the types must be known at compile time.

The book adds that concepts cannot *fully* express semantics, yet they still
express expected behavior — exactly like the standard library's `InputIt` and
`OutputIt` named template parameters, which communicate behavior (traversal,
dereference, eventual termination) beyond mere syntax. Because a concept is an
LSP abstraction, it is also subject to the **Interface Segregation Principle**
(layer small concepts, the way the standard iterator concepts build on one
another). From this guideline onward the book uses the single word *concept* to
mean any such set of requirements — base class or C++20 concept alike.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_RuntimeAbstraction_BaseClass` | The runtime abstraction: a `Document` base class with pure virtual `exportToJSON()` / `serialize()`. `useDocument(Document const&)` depends only on the abstraction; `PDF` and `Word` are dispatched dynamically, including from a heterogeneous container. |
| 02 | `02_CompileTimeAbstraction_Concept` | The compile-time abstraction: the *same* operations expressed as a C++20 `concept Document`. `useDocument()` is a constrained template; `PDF` and `Word` are unrelated value types selected at compile time. `static_assert`s prove the concept is checked statically. |
| 03 | `03_SameExpectations` | Two sides of one coin: a single `PDF` type derives from the base class **and** satisfies the concept. `useDocument()` is called in both styles with identical behavior; a `static_assert` confirms the expectations coincide. |

Each sample is a single self-contained `main.cpp` using the standard library
only; the external `ByteStream` is replaced by a small std-based stub.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 7

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 7
```

## Notes

- **Same intent, different binding moment.** The only real difference between
  the two abstractions is *when* the type is checked and the operation bound —
  run time (vtable) versus compile time (overload resolution on a constrained
  template).
- **LSP applies to both.** A derived class and a concept-satisfying type must
  honor the *expected behavior*, not merely match the signatures. Violating the
  behavior breaks `useDocument()` either way.
- **Trade-offs.** Prefer the base class for heterogeneous collections and stable
  binary boundaries; prefer the concept for value types and library-style code
  where types are known and you want zero dispatch cost. Guideline 36 weighs
  this runtime-versus-compile-time trade-off in depth.
- **Concepts express behavior, not just syntax.** Even pre-C++20 named template
  parameters (`InputIt`, `OutputIt`) communicate expectations; document them so
  callers know the behavior a template relies on.

## Related

→ Guideline 6 (Adhere to the Expected Behavior of Abstractions) establishes the
LSP this guideline extends to templates.
→ Guideline 3 (Separate Interfaces) — concepts, being LSP abstractions, are
subject to the ISP too; keep them small and layered.
→ Guideline 36 (Runtime vs. Compile Time Abstraction) explores the trade-off
between the two styles shown here.
