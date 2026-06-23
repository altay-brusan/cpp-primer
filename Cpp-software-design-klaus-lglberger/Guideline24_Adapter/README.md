# Guideline 24 — Use Adapters to Standardize Interfaces

> **Concern:** A class can have exactly the functionality you need yet the
> **wrong interface** — different function names, free functions instead of
> members, the wrong base class. The **Adapter** design pattern wraps that class
> so it conforms to the interface a client already expects, *without modifying
> either side*. Its intent: *"Convert the interface of a class into another
> interface clients expect. Adapter lets classes work together that couldn't
> otherwise because of incompatible interfaces."*

## The idea

The book continues the *Document* example. A client codes against the
segregated `Document` abstraction (`JSONExportable::exportToJSON` and
`Serializable::serialize`), and the existing `Word` document fits it. Then a
third-party `OpenPages` class arrives: it does everything needed, but speaks a
different dialect — serialization is a member `convertToBytes`, JSON export is a
**free** `exportToJSONFormat`, and it does not derive from `Document`. The
functionality is right there, but the interfaces are incompatible.

The Adapter pattern bridges the gap. A `Pages` class **is a** `Document` and
re-presents `OpenPages` through the expected interface, forwarding each call to
the matching adaptee operation. The integration is **nonintrusive**: neither
`OpenPages` nor `Document` changes.

- **Object adapter (composition).** `Pages` *stores* an `OpenPages` and
  delegates to it. This is the book's preferred default — it builds on
  composition (Guideline 20) and is the most flexible form.
- **Class adapter (inheritance).** `Pages` privately *inherits* `OpenPages`
  (is-implemented-in-terms-of). Use it only for specific reasons: overriding a
  virtual of the adaptee, needing a protected member, controlling base
  construction order, sharing a virtual base, or exploiting the Empty Base
  Optimization. Otherwise prefer the object adapter.
- **Standard-library adapters.** `std::stack`, `std::queue`, and
  `std::priority_queue` are container *adaptors*: they wrap a container and
  re-present it through a narrowed, purpose-built interface. The free `begin`
  and `end` are *function adapters* (shims) doing the same via overloading.

Mapping need not be one to one — an adapter freely maps the expected set of
functions onto the available set. And the same caution as the book's *turkey is
not a duck*: watch for **LSP** violations; only adapt when the adaptee truly
honors the target interface's expectations.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_Problem_IncompatibleInterface` | A client drives a `Document`; `Word` fits, but the useful third-party `OpenPages` has the wrong names (`convertToBytes`, free `exportToJSONFormat`) and the wrong base, so it cannot reach the client. Compiles and runs; the would-be call is shown commented out. |
| 02 | `02_Solution_ObjectAdapter` | Object adapter: `Pages : Document` *stores* an `OpenPages` and forwards `serialize`/`exportToJSON` to it. The unchanged client now drives `Word` and `Pages` uniformly. |
| 03 | `03_Solution_ClassAdapter` | Class adapter: `Pages : Document, private OpenPages`. Same result via private inheritance; notes when this form is justified over composition. |
| 04 | `04_StdContainerAdapter` | Library adapters: an abstract `Stack<T>` with a `VectorStack<T>` adapter (runtime), alongside `std::stack` over a `std::vector` (compile-time container adaptor). |

Each sample is a single self-contained `main.cpp` using the standard library
only; the "third-party" `OpenPages` is a tiny local stub.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 24

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 24
```

## Notes

- **Object vs class adapter.** Both have the same intent; they differ in
  mechanism. An object adapter *composes* the adaptee (owns an instance and
  delegates); a class adapter *inherits* it (privately). Favor the object
  adapter — composition over inheritance (Guideline 20) — and reach for the
  class adapter only when you must override a virtual, access a protected
  member, control base construction order, share a virtual base, or benefit
  from the Empty Base Optimization.
- **Nonintrusive integration.** The adapter is added on top; neither the
  adaptee nor the target interface is touched. Anyone can adapt one interface to
  another, which keeps the design open for extension (OCP) and the adapter's
  single responsibility the interface mapping (SRP).
- **Adapter vs Strategy.** Structurally similar, different intent. Adapter
  *standardizes* an interface so incompatible pieces fit, configured once;
  Strategy injects *one aspect* of behavior, meant to be reconfigured.
- **Dynamic and static.** Adapter works for runtime polymorphism (the `Pages`
  and `Stack` examples) and compile-time polymorphism (`std::stack`, and the
  function adapters `begin`/`end`).
- **Mind the LSP.** Adapter makes it easy to combine things that look alike but
  are not — the book's turkey forced into a duck choir. Always check that the
  adaptee honors the expected behavior of the target interface.

## Related

→ Guideline 3 (Separate Interfaces) gives the segregated `Document` interfaces
used here. → Guideline 20 (Favor Composition over Inheritance) is why the object
adapter is the default. → Guideline 19 (Strategy) is the pattern Adapter is most
often confused with. → Guideline 14 (Use a Pattern's Name) discusses whether to
call the class `Pages` or `PagesAdapter`.
