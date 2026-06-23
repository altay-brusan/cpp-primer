# Guideline 25 — Apply Observers as an Abstract Notification Mechanism

> **Concern:** We often need feedback the *moment* some state changes (a name is
> edited, a job is queued, a result is ready). But the observed entity — the
> **subject** — must not depend on the concrete reactions to that change. A
> direct dependency from subject to its many reactions makes the code hard to
> change and extend. The **Observer** design pattern extracts "the need to add
> new reactions" as the variation point and turns it into an abstraction, the
> **Observer** interface, giving a decoupled **one-to-many** relationship.

## The idea

The book frames the Observer's intent as: *"Define a one-to-many dependency
between objects so that when one object changes state, all its dependents are
notified and updated automatically."* The subject should be **oblivious** to the
potentially many kinds of observers — that obliviousness is the whole point.

Extracting the `Observer` base class is the **Single Responsibility Principle**
in action (isolate the variation point), which in turn enables the **Open–Closed
Principle**: anyone can add a new observer without modifying existing code. If the
`Observer` abstraction is owned at a high architectural level, the **Dependency
Inversion Principle** is satisfied too.

The book gives three ways to define `update()`:

- **Push observer.** `update()` is handed the changed values directly (possibly
  several overloads, one per kind of change). Efficient and minimally coupled to
  the subject — but it depends on the argument list, so any change to what is
  pushed ripples into every observer, and observers always get *all* the data
  whether they need it or not.
- **Pull observer.** `update(const Subject&)` hands only a reference to the
  subject; the observer pulls what it wants. Independent of the argument list,
  but now strongly coupled to the subject's interface, and an observer may have
  to "search" for what actually changed.
- **Pull + tag (the book's choice, used here).** `update(const Subject&, StateTag)`
  adds a subject-specific tag naming *which* property changed, so an observer can
  cheaply decide whether the change is interesting. `Observer` is a **class
  template** over `Subject` and `StateTag`, lifting it to the top of the
  architecture so many subjects can reuse it.

Observers are stored as **raw, non-owning pointers** in a `std::set`. A pointer
is just a stable unique handle (C++ Core Guideline F.7); an owning smart pointer
would be the wrong tool, so **observer lifetime stays with the caller**.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_Solution_Observer` | The classic template-based Observer: `Observer<Subject, StateTag>` interface, a `Person` subject with `attach`/`detach`/`notify`, and two concrete observers (`NameObserver`, `AddressObserver`) using **pull + tag**. Shows duplicate `attach` rejected by the set and a `detach` silencing one channel. |
| 02 | `02_Solution_StdFunction` | The value-semantics form: `Observer` becomes an **Adapter over `std::function`** — no inheritance, no virtuals. One observer is built from a **free function**, another from a **stateful lambda** that counts moves across subjects. Fits a pull observer with a single `update()`. |

Each sample is one self-contained `main.cpp` using the standard library only;
`main()` registers observers and triggers notifications.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 25

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 25
```

## Notes

- **Push vs pull.** Push hands the changed values to `update()` (fast, low
  coupling to the subject, but coupled to the argument list and possibly
  wasteful). Pull hands the subject and lets the observer fetch what it wants
  (independent of arguments, but coupled to the subject and may have to search).
  **Pull + tag** is the book's recommended middle ground and is what sample 01
  uses; sample 02 is also a single-`update()` pull observer.
- **`std::function` is for a single `update()`.** A value-based observer with one
  callable cannot model a push observer that needs *several* `update()`
  overloads — one `std::function` holds one callable. For that, generalize with
  **Type Erasure**.
- **Why keep the `Observer` class around `std::function`?** Functionally it adds
  nothing, but `std::function` is value semantic and copies freely; for a
  *stateful* observer you do not want a copy to be the one notified. Wrapping it
  in an `Observer` referred to by a stable address avoids that and provides the
  unique handle that `attach`/`detach` need.
- **Lifetime of observers.** The subject only **borrows** observer addresses; it
  never owns them. Each observer must outlive its registration, or detach before
  it dies, otherwise the set holds a dangling pointer.
- **`notify()` is written carefully.** It advances the iterator *before* the
  callback so an observer may detach **itself** during `update()`. It still does
  not cope with `attach()` during iteration, nor with concurrency — the book is
  explicit that these implementation details (registration order, multiple
  registrations, thread safety) are a "can of worms" left out of scope.
- **Beware over-connection.** Overusing observers can build a tangled web and
  even an infinite callback loop. A sound architecture keeps notifications flowing
  along a **directed acyclic graph** toward lower levels.

## Related

→ Guideline 2 (Design for Change) and Guideline 5 (Design for Extension) are the
SRP/OCP foundation the Observer rests on. → Guideline 22 (Prefer Value Semantics)
motivates the `std::function` form. → Guideline 24 (Use Adapters to Standardize
Interfaces) explains why the value-based `Observer` is an Adapter. → Chapter 8
(Type Erasure) generalizes the single-callable limitation.
