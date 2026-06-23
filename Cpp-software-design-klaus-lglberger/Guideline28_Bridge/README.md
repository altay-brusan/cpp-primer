# Guideline 28 — Build Bridges to Remove Physical Dependencies

> **Concern:** A class that stores its implementation **by value** forces its
> header to include the implementation's header, creating a transitive
> **physical (compile-time) dependency** and leaking the in-memory layout to
> every client. The **Bridge** design pattern (and its simplest form, the
> **Pimpl idiom**) hides the implementation behind a pointer so the details — and
> their headers — are no longer compile-time dependencies of clients. The result
> is a *compilation firewall*: better encapsulation, faster rebuilds, and ABI
> stability.

## The idea

The book's `ElectricCar` stores an `ElectricEngine` by value. Because the
compiler must know an `ElectricEngine`'s size to size an `ElectricCar`,
`ElectricCar.h` is forced to `#include <ElectricEngine.h>`. Now every translation
unit that includes the car header transitively depends on the engine header: any
engine change recompiles, retests, and possibly redeploys the lot. Worse,
`private` is an **access** label, not a **visibility** label — the engine member
is visible to everyone, so the layout is public and the ABI is frozen in plain
sight.

Storing a raw/`unique_ptr` to a *concrete* engine removes the physical include
but still leaks *which* engine is used. To remove that too, introduce an
**abstraction**:

- **Pimpl idiom (one implementation).** Move every member into a private nested
  `struct Impl`, declared in the header and defined in the source file; the class
  keeps a single `std::unique_ptr<Impl>`. This is the local, nonpolymorphic
  Bridge — full decoupling with no base class.
- **Full Bridge (many implementations).** Replace the concrete impl with a pure
  virtual `Engine` base and hold a `std::unique_ptr<Engine>` pimpl, factored into
  a reusable `Car` base. The concrete engine becomes a secret, set internally.

The telltale that distinguishes **Bridge** from **Strategy** is *how the pointer
is set*: Bridge chooses the implementation **internally** with `make_unique`
(physical decoupling, a structural pattern); Strategy accepts it **from outside**
(logical decoupling, a behavioral pattern).

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_Problem_PhysicalDependency` | `ElectricCar` holds an `ElectricEngine` **by value**, so its header must include the engine header: the layout leaks and any engine change forces recompilation and breaks ABI. Compiles and runs. |
| 02 | `02_Solution_Pimpl` | The Pimpl idiom: a forward-declared nested `Impl`, a `unique_ptr<Impl>`, members forwarding to it. The destructor, copy ops, and getter are defined where `Impl` is complete. One impl, no abstraction. |
| 03 | `03_Solution_Bridge` | The full Bridge: an abstract `Engine` behind a `unique_ptr<Engine>` pimpl in a `Car` base. The concrete engine is chosen internally and `upgrade()` swaps it at runtime with no client noticing. |

Each sample is one self-contained `main.cpp`; `main()` builds the class and
exercises it. To stay one translation unit, the `.h`/`.cpp` boundary is marked
with comments rather than split across files.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 28

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 28
```

Standard library only; engines are simulated with console output.

## Notes

- **Pimpl vs. Bridge.** Pimpl is the simplest, *nonpolymorphic* Bridge: use it
  when there is exactly one implementation and you only need to hide it. The full
  Bridge adds an abstract base so the implementation can also *vary* — many engine
  kinds behind one `Engine` interface.
- **Compile-time benefit.** Hiding the impl behind a pointer turns the class into
  a compilation firewall: changing, adding, or removing impl members recompiles
  only the source file, never the clients. This is the physical decoupling the
  guideline is named for.
- **ABI stability.** A pimpl class is always one pointer wide, so its in-memory
  size never changes when the implementation does — essential when the binary
  layout must stay fixed.
- **The destructor wrinkle.** A `unique_ptr` to an **incomplete** type cannot
  synthesize its deleter. Declare the destructor in the class and define it
  (`= default`) where `Impl` is complete; the same incompleteness rule forces
  copy operations and even trivial getters out of the header.
- **The indirection cost.** Bridge is not free: an extra pointer hop on every
  access, a dynamic allocation per object, lost inlining, the pointer's memory,
  and (for the full Bridge) a virtual call. Decide case by case and measure —
  *it depends*.
- **Bridge vs. Strategy.** Same structure, different intent. Bridge sets the impl
  internally to cut **physical** dependencies (structural); Strategy injects it
  from outside to cut **logical** dependencies (behavioral).

## Related

→ Guideline 2 (Design for Change) motivates isolating what changes. → Guideline
19 (Strategy) is the behavioral twin distinguished by *who sets the pointer*. →
Guideline 29 (Bridge Performance) quantifies the indirection cost previewed here.
