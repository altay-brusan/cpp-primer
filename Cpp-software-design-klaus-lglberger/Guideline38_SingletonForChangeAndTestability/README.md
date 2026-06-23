# Guideline 38 — Design Singletons for Change and Testability

> **Concern:** A Singleton represents **global state**, and the real damage is
> not the "one instance" rule but that callers depend on a **concrete**
> Singleton directly (`Database::instance()`). That hidden, low-level dependency
> violates the Dependency Inversion Principle and leaves **no seam** to
> substitute a test double. The fix is to **invert the dependency** with the
> **Strategy** design pattern: depend on an abstraction, inject the
> implementation.

## The idea

Singletons usually stand for genuinely global aspects — the system-wide
database, logger, clock, or configuration. That global state is the intrinsic
problem (it is opaque, hard to reason about, and risks the static initialization
order fiasco), and it is *not* solved by banning Singletons. Where a global
aspect is real, the book's advice is to use Singleton **judiciously**, prefer
**unidirectional data flow**, and — crucially — **design for change and
testability**.

The trouble in the book's example is that `Widget` and `Gadget` call
`Database::instance().read()` / `.write()` directly. `Database` is a *concrete
implementation*, not an abstraction, so:

- **Dependencies point the wrong way.** Using code depends on a low-level
  detail. The Dependency Inversion Principle fails; in effect there is no
  architecture.
- **The dependency is invisible.** `doSomething()`'s signature says nothing
  about reaching into global state.
- **Testability collapses.** Nothing lets you substitute the `Database` with a
  stub, mock, or fake, so every test must drag in the one real database.

The remedy is the **Strategy** pattern. Introduce a `PersistenceInterface`
abstraction on the **high** level (split into a public interface and private
virtual implementation, like `std::pmr::memory_resource`). Add a global point of
**access**, `get_persistence_interface()`, and a global point of **injection**,
`set_persistence_interface()`, over a single `instance` pointer.
`get_persistence_interface()` lazily builds a default `Database` via an
Immediately Invoked Lambda Expression so the default is created only if nothing
was injected first. `Database` now *inherits* from `PersistenceInterface` and
becomes a replaceable implementation detail on the **lowest** level. The
dependencies are inverted, and a test simply injects a fake.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_Problem_DirectSingleton` | `Widget` and `Gadget` call the concrete `Database::instance().read()` / `.write()` directly. The dependency points at the low-level detail and there is no seam to substitute a fake, so the code cannot be tested without the real database. Compiles and runs. |
| 02 | `02_Solution_InvertedDependency` | A `PersistenceInterface` abstraction plus `get_persistence_interface()` / `set_persistence_interface()` over one `instance` pointer. Production uses a lazily-created `Database` Singleton; a tiny test injects a `CustomPersistence` fake and asserts the recorded calls — substitutability and testability without any real database. |

Each sample is one self-contained `main.cpp`. The solution's `main()` runs the
production path and then a small inline test that swaps in the fake.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 38

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 38
```

Each sample uses the standard library only; the "real database" is simulated
with console output.

## Notes

- **Invert the dependency.** The defect is not the single instance but the
  *direction* of the dependency. Depending on `PersistenceInterface` instead of
  `Database` turns the arrow toward the high-level abstraction and restores the
  Dependency Inversion Principle.
- **Two global points: access and injection.** `get_persistence_interface()`
  hands out the current implementation; `set_persistence_interface()` is the
  injection seam. Call the setter at the **start of the program** or the **start
  of a single test**, not at arbitrary points — like `std::move`, calling it
  mid-flight pulls the rug out from under other code.
- **Lazy default via an IILE.** Two static locals plus an immediately invoked
  lambda create the default `Database` only when no implementation was injected
  first, so a test that injects up front never builds the real database.
- **Testability is the payoff.** A `CustomPersistence` fake records its calls;
  the test verifies behavior with fast, isolated assertions and no real I/O.
- **`std::pmr` is the standard's own example.** `std::pmr::get_default_resource`
  / `set_default_resource` over the `std::pmr::memory_resource` abstraction are
  exactly this pattern: a Singleton you can replace.
- **Prefer unidirectional data flow,** and remember dependency injection has
  more local forms (constructor or parameter injection); the global access point
  is one valid choice once the dependency has been inverted.

## Related

→ Guideline 37 (Treat Singleton as an Implementation Pattern) introduces the
Meyers' Singleton this guideline refactors. → Guideline 2 (Design for Change)
and Guideline 4 (Design for Testability) are the goals served here.
→ Guideline 9 (Ownership of Abstractions) and Guideline 19 (Strategy) supply the
dependency-inversion and Strategy machinery used by the fix.
