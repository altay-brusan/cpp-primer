# Guideline 3 — Separate Interfaces to Avoid Artificial Coupling

> **Concern:** Coupling does not only live in implementations — it lives in
> **interfaces** too. When one interface aggregates orthogonal concerns, every
> client is forced to depend on methods it never calls, so any change to one
> concern ripples to all users. Adhere to the **Interface Segregation Principle
> (ISP)** — *clients should not be forced to depend on methods they do not use* —
> to split fat interfaces into focused ones.

## The idea

The book revisits the *Document* example from Guideline 2, but this time the
focus is the interface as a whole rather than a single function. A `Document`
base class that demands both `exportToJSON()` and `serialize(ByteStream&)`
welds two unrelated aspects together. A client like `exportDocument()` that only
wants JSON nevertheless depends, through the `Document` interface, on
serialization and on the `ByteStream` type. Change `ByteStream` or the signature
of `serialize()` and **every** user of `Document` — even JSON-only ones — must
be recompiled, retested, and possibly redeployed.

- **The smell is artificial coupling.** Interfaces are supposed to *decouple*,
  but a fat interface that bundles orthogonal concerns introduces dependencies
  that are entirely unnecessary.
- **The fix is segregation.** Split the fat interface into `JSONExportable` and
  `Serializable`. `Document` still represents the full requirement on all
  documents by inheriting from both, so nothing is lost — but clients now depend
  only on the concern they actually use.
- **ISP is a special case of the SRP.** Iglberger notes that segregating
  interfaces is really applying the Single-Responsibility Principle to
  interfaces: one interface, one reason to change. He keeps it as a distinct,
  important case because it is so easy to accidentally couple aspects together,
  and interfaces are very hard to change later.
- **It applies to templates too.** A template's constraints *are* its interface.
  `std::copy` requires only `input_iterator` plus `output_iterator`, never the
  stronger `forward_iterator`, so it stays usable with single-pass sources like
  input streams. Over-constraining a template is the same coupling smell as a
  fat base class.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 1 | `01_Problem_FatIface` | One fat `Document` interface couples JSON export and serialization, so a JSON-only client transitively depends on `serialize()` and `ByteStream`. Bad design that still compiles and runs. |
| 2 | `02_Solution_SplitIface` | The interface is segregated into `JSONExportable` and `Serializable`; `exportDocument()` depends only on `JSONExportable`, decoupling it from serialization and `ByteStream`. |
| 3 | `03_Solution_Templates` | ISP for generic code: `myCopy` requires only `input_iterator` plus `output_iterator`, so it copies from a single-pass source; a `static_assert` shows an over-constrained `forward_iterator` requirement would reject it. |

## Build & run

From the repository root:

```powershell
# Build and run a specific sample interactively
./run.ps1 -Guideline 3

# Or compile-check every sample of this guideline
./run.ps1 -Verify -Guideline 3
```

Each sample is a single self-contained `main.cpp` compiled with MSVC
(`/std:c++latest`, C++23). No external libraries are used: `ByteStream` is a tiny
inline stub standing in for a real serialization library, and the template
sample uses only `<iterator>` from the standard library.

## Notes

- The problem sample is deliberately bad **design** but valid **code** — it
  compiles and runs so the coupling can be observed, not just described.
- `Document` does not disappear after segregation; it composes the two roles via
  multiple inheritance, exactly as the book shows.
- The over-constrained template variant is documented with a `static_assert`
  rather than uncompilable code, so the whole guideline keeps compiling.

## Related

← Guideline 2 (Design for Change) introduced the *Document* example and the
distinction between necessary and artificial dependencies. → Guideline 19 (Use
Strategy to Isolate How Things Are Done) shows how easily orthogonal aspects get
coupled into an interface in practice.
