# Guideline 23 — Prefer a Value-Based Implementation of Strategy and Command

> **Concern:** Guideline 19 (Strategy) and Guideline 21 (Command) solved
> decoupling with **inheritance** — a base class with one virtual function,
> injected through a pointer. But Guideline 22 argues for **value semantics over
> reference semantics**. A Strategy or a Command is, at its core, just a *single
> callable*. `std::function` — a value-based, type-erased callable — abstracts
> exactly that, so we can implement both patterns **without any base class**,
> pointers, or lifetime management.

## The idea

`std::function<R(Args...)>` stores **any** callable matching its function type: a
free function, a function object, or a lambda. It is a value — copying it
deep-copies the contained callable, and an empty instance throws
`std::bad_function_call` when invoked. That single abstraction is precisely what
one virtual function provided in the classic patterns.

- **Strategy via `std::function`.** Each shape replaces its `DrawStrategy` base
  class with a `std::function` data member. A backend no longer derives from
  anything — it is supplied as a lambda, free function, or functor. The strategy
  is taken **by value and moved** into the member: the book shows this is an
  elegant compromise (an lvalue costs one copy plus one move; an rvalue costs two
  moves), avoiding the need for separate lvalue and rvalue constructor overloads.
- **Command via `std::function`.** A command that only needs `execute()` is a
  single callable, so a command queue becomes a
  `std::vector<std::function<void()>>`. Lambdas capture the arguments each action
  needs, replacing per-command subclasses. No `Command` base class, no owning
  pointers.
- **The honest shortcoming.** `std::function` replaces only **one** virtual
  function. A Command with `undo()` needs **two** `std::function` members; more
  varying operations means more members and a clumsier interface. For that case
  the book points to **Type Erasure** (Chapter 8) as the generalization of this
  value-based idea.

The benefits: cleaner, more readable code; no pointer lifetime management; very
loose coupling (`std::function` acts as a compilation firewall) plus the freedom
to implement behavior in any callable form. The cost: a potential performance
overhead in some standard `std::function` implementations.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_Strategy_StdFunction` | A shape holds its draw strategy as a `std::function`, set from a free function, a lambda, and a stateful functor. No `DrawStrategy` base class; copying a shape deep-copies its strategy. |
| 02 | `02_Command_StdFunction` | Commands as `std::function<void()>` collected in a `std::vector` and replayed. Lambdas capture their arguments; no `Command` base class, no owning pointers. |
| 03 | `03_Command_Undo_TwoFunctions` | A calculator command with undo needs **two** `std::function` members (do and undo). Demonstrates the book's documented limit: one `std::function` per virtual function. |

Each sample is one self-contained `main.cpp` whose `main()` prints its results;
backends are simulated with console output.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 23

# Build+run a specific sample (e.g. the Command queue):
./run.ps1 -Guideline 23 -Sample 2

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 23
```

Standard library only (`<functional>` and friends); C++20 or later.

## Notes

- **Strategy and Command collapse to the same tool.** Both isolate a single
  callable, so both are implemented the same way — `std::function` held by value.
  This is the value-semantics counterpart to the inheritance-based Guideline 19
  and Guideline 21.
- **Pass by value, then move.** Taking the `std::function` by value and moving it
  into the member is the recommended compromise: efficient for both lvalues and
  rvalues without writing a second `&&` constructor overload.
- **Flexibility vs. small overhead.** The upside is huge flexibility (any
  callable plugs in) and very loose coupling. The downside is that some standard
  `std::function` implementations carry a measurable runtime overhead versus a
  hand-rolled type-erased equivalent or a classic virtual call; for hot paths,
  measure, and consider a manual Type Erasure wrapper.
- **One callable per `std::function`.** It abstracts a single virtual function
  only. Multiple varying operations (e.g. `execute()` plus `undo()`) need
  multiple members; beyond a couple, prefer a custom Type Erasure type.
- **Value semantics removes a class of bugs.** No raw or smart pointers means no
  lifetime management and no dangling references; copies are independent.

## Related

→ Guideline 19 (Strategy) and Guideline 21 (Command) are the inheritance-based
originals this guideline reworks. → Guideline 22 (Prefer Value Semantics over
Reference Semantics) is the motivation. → Chapter 8 / Type Erasure generalizes
the value-based approach when one `std::function` is not enough.
