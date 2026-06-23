# Guideline 21 — Use Command to Isolate What Things Are Done

> **Concern:** *What* is done — which action a calculator performs, which task a
> queue runs — is a **variation point**. Leave the action implicit (an enum plus a
> switch) and it cannot be passed, queued, stored, or undone, and every new
> action forces a change to existing code. The **Command** design pattern
> encapsulates a request *as an object* so it can be parameterized, queued,
> logged, and — optionally — undone, and so new actions are added **without
> modifying existing code**.

## The idea

The book uses a calculator. A first version applies operations immediately by
switching on an enum. It works, but the action is never captured: there is no
record to roll back, and adding an operation means editing the enum and the
switch. The fix is to **identify the action as a variation point and extract
it** — the intent of Command: *"Encapsulate a request as an object, thereby
letting you parameterize clients with different requests, queue or log requests,
and support undoable operations."*

- **Command with undo (the calculator).** A `CalculatorCommand` abstraction
  declares `execute()` and `undo()`. `Add` and `Subtract` (and a newly added
  `Multiply`) each know how to apply *and* reverse themselves. The `Calculator`
  is the **Invoker**: it keeps a current value and a **stack** of executed
  commands; `compute()` runs and stores a command, `undoLast()` pops and reverses
  it. Because the variation point is extracted, `compute()` and `undoLast()` are
  not virtual, and a new operation is just a new class — the SRP enabling the OCP.
  Ownership flowing through `unique_ptr` to the high level also serves the DIP.
- **Command without undo (the task queue).** The book's second classic example is
  a thread pool; here it is a deterministic `TaskQueue`. It schedules any
  `Command` through the abstraction and runs each later, fully decoupled from
  *what* the task does. `FormatCommand` and `PrintCommand` have nothing to roll
  back — and that is fine. The book treats **undo as an optional feature** of
  Command, not a defining one (which is why `std::for_each` still takes a Command).

Per the book's caution: the line between Command and Strategy is **fluid** — they
are structurally identical, differing only in *intent*. Do not lose friends
arguing which one it is; exploit that both isolate change and serve the SRP and
OCP.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_Problem_NoUndo` | A calculator that applies operations via an enum plus a switch. The action is never an object, so nothing can be undone and every new operation forces an edit to the enum and the switch. Compiles and runs. |
| 02 | `02_Solution_Command` | The Command pattern: a `CalculatorCommand` base with `execute()`/`undo()`, `Add`/`Subtract`/`Multiply` commands, and a `Calculator` invoker with an **undo stack**. A new `Multiply` is added touching no existing class. |
| 03 | `03_Command_TaskQueue` | Command **without** undo: a `TaskQueue` schedules and later runs any `Command` (`FormatCommand`, `PrintCommand`), decoupled from what each task does — showing undo is optional, not defining. |

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 21

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 21
```

Each sample is a single self-contained `main.cpp` using the standard library
only; backends (disk format, print job) are simulated with console output.

## Notes

- **Command isolates the WHAT.** It captures *which* action to perform as an
  object so it can be passed, queued, stored, logged, and reversed. Strategy
  isolates the **HOW** — *how* an operation is carried out — and is injected to
  configure an object.
- **Command vs. Strategy — structurally identical.** The book is explicit: from
  an implementation point of view there is no difference. The difference is
  entirely **intent**. `std::partition` takes a Strategy (how to select);
  `std::for_each` takes a Command (what to do to each element).
- **Two tells.** (1) If you inject the action to **configure** an object
  (dependency injection), it is most likely Strategy; if the action is performed
  **directly**, it is most likely Command — the calculator evaluates immediately,
  so it is Command. (2) If the action carries a self contained `undo()`, it is
  most likely Command; Strategy usually lacks the information to roll back. The
  calculator could instead inject a `CalculatorStrategy`, but a sensible undo
  becomes hard — a hint it is naturally a Command.
- **undo() is optional.** Its absence is *not* proof of Strategy: `std::for_each`
  expects a Command yet needs no undo. The book even argues undo is a necessity
  rather than a strength — only the action itself can cheaply reverse what it did.
- **Trade-off.** The GoF base class form costs one virtual indirection per
  command. As ever — *it depends* whether the flexibility is worth it.

## Related

→ Guideline 19 (Use Strategy to Isolate How Things Are Done) is Command's twin —
same structure, opposite intent. → Guideline 5 (Design for Extension) sets up the
OCP this pattern serves. → Guideline 23 (Prefer a Value-Based Implementation of
Strategy and Command) revisits both with value semantics.
