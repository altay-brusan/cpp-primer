# Guideline 5 — Design for Extension

> **Concern:** Code that can no longer grow has reached the end of its life, so
> **extensibility** must be a primary design goal. The **Open-Closed Principle
> (OCP)** captures it: software artifacts should be *open for extension but
> closed for modification* — you add new behavior by adding new code, not by
> editing code that already works.

## The idea

The book uses the *Document* serialization example. A naive design tags every
document's byte stream with a central `DocumentType` enumeration and serializes
through a `switch` over that enum. It compiles and runs, but it is wrong in a
subtle way: the enum sits on the *same architectural level* as `PDF` and `Word`,
so every format depends on it and therefore on every other format. `PDF`
"knows about" `Word`, and vice versa — an **artificial coupling**.

Adding a plain `XML` format then forces you to edit the enum *and* the central
`switch`. At minimum that recompiles `PDF` and `Word`; at worst it stops third
parties (who cannot touch the central enum) from extending the code at all. That
is exactly what the OCP advises against: extension by **modifying** existing code.

The fix is to **separate concerns** and provide a real extension point:

- **Runtime extension (base class).** Give `Document` a pure virtual
  `serialize()` so each type owns its own format. The shared enum disappears,
  the coupling disappears, and a new format is one new derived class. Existing
  types "don't see or feel a thing, not even a recompilation."
- **Compile-time extension (overload set / templates / specialization).** The
  book stresses the OCP is *not* only about runtime polymorphism. The Standard
  Library is designed for extension with **no base classes** — `std::swap`
  (function overloading), `std::find` (templates), `std::hash` (template
  specialization). A new type plugs into a generic algorithm via ADL by adding
  one free overload, modifying nothing.

And per the book's closing caution: do not *prematurely* design for extension.
Honor **YAGNI** — add the abstraction when you know how the code will evolve.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_Problem_EnumSwitch` | Closed design: a `DocumentType` enum plus a central `serialize()` `switch`. Adding a type forces edits to the enum and the switch, recoupling `PDF` and `Word` — an OCP violation. Compiles and runs. |
| 02 | `02_Solution_VirtualFunction` | Runtime extension: a base class with virtual `serialize()`. The new `XML` type is added by deriving one class and overriding one function — no edits to existing code. |
| 03 | `03_Solution_CompileTime` | Compile-time extension: a generic `toBytes()` algorithm plus an overload set resolved by ADL (the `std::swap` style). The new `XML` type plugs in by adding one free `serialize()` overload — no base class, no edits. |

Each sample's `main()` exercises at least two types so the extension point is
concrete; the solutions add a third (`XML`) to show that extension touches no
existing code.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 5

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 5
```

Each sample is a single self-contained `main.cpp` using the standard library
only; the external `ByteStream` is replaced by a small std-based stub.

## Notes

- The enum-plus-switch problem is *silent*: a forgotten `switch` case may not
  warn, so a new type can ship with a missing or wrong byte header.
- Separation of concerns (each type serializing itself) resolves the OCP
  violation and the artificial coupling together — the book even notes OCP and
  the SRP are closely related for this reason.
- Lower levels may still change: a real serialization component still needs to
  know all document types. That is allowed — the OCP forbids modifying code on
  the *same or higher* architectural levels, not on lower (depending) levels.
- Prefer base classes for runtime/heterogeneous collections; prefer overload
  sets, templates, and specialization for value types and library-style code.

## Related

→ Guideline 2 (Design for Change) introduces the *Document* example.
→ Guideline 3 (Separate Interfaces) attacks the same artificial coupling.
→ Guideline 15 (Addition of Types or Operations) makes the explicit choice of
*what* to keep open for extension.
