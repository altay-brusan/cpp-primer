# Guideline 4 — Design for Testability

> **Concern:** Tests are your protection layer against accidentally breaking things,
> so your software must be **testable**. A function that is important enough to test
> but is buried in a class's `private` section is *misplaced*. Rather than hacking
> access to it, **separate concerns**: extract it as a non-member non-friend function
> (or a small class) that has a real, directly testable interface.

## The idea

The book poses a challenge: `Widget` has a `private` member function
`updateCollection()` that reorganizes its `std::vector<Blob>`, and we decide it is
important enough to test. But it is private, so there is no direct way to call it. Every
tempting workaround makes the design worse:

- **White-box test through a public function** (call `addBlob`, which internally calls
  `updateCollection`). The test now depends on an *implementation detail*. If `addBlob`
  is rewritten so it no longer calls `updateCollection`, the test silently stops testing
  what it was written for — you lose coverage without noticing. A **black-box** test,
  which checks only observable behavior, is what we actually want.
- **Make it public.** `updateCollection` guards an invariant and should be called only at
  the right time — not something to entrust to every user.
- **`friend class TestWidget`.** It works, but now the *production* code knows about the
  *test* code: an artificial, cyclic dependency. In C++, `friend` is not your friend.
- **`protected` + a test class that inherits `Widget`.** Abuses inheritance purely to
  gain access; almost as open as making it public. *Inheritance is rarely the answer.*
- **`#define private public`.** Once you reach for the preprocessor to break into the
  private section, all is lost.

**The true solution is separation of concerns.** Extract `updateCollection()` from the
class. If it is stateless, make it a **free function** taking the data as its first
argument; if it carries state, extract a small **class**. Either way it gains a true,
directly testable interface. This also *increases* encapsulation (Meyers: prefer
non-member non-friend functions), because the extracted code can touch only `Widget`'s
public surface — and it reduces coupling, since the logic can now change and be reused in
isolation.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 1 | `01_Problem_PrivateMethod/WidgetProblem.cpp` | The private `updateCollection` and the flawed workarounds — a white-box test through `addBlob` and a `friend class TestWidget` — both compile and pass, but each adds an artificial dependency. |
| 2 | `02_Solution_FreeFunction/` (`Collection.h`, `WidgetFreeFunction.cpp`) | The logic extracted as a free function `widgetDetails::updateCollection(std::vector<Blob>&)`, tested directly with just a vector — no `Widget`, no `friend`. |
| 3 | `03_Solution_ExtractedClass/` (`BlobCollection.h`, `WidgetExtractedClass.cpp`) | The stateful variant: a `widgetDetails::BlobCollection` class with a public interface, tested on its own; `Widget` composes it. |

Each sample is self-contained (local headers only) and uses a tiny hand-rolled
`assert` / printed `PASS`/`FAIL` harness — **no external test framework**.

## Build & run

From the repository root:

```powershell
./run.ps1 -Guideline 4            # interactive: pick a sample and run it
./run.ps1 -Guideline 4 -Sample 2  # build + run sample 2 directly
./run.ps1 -Verify -Guideline 4    # compile-check every sample
```

Builds with MSVC (`/std:c++latest`, C++23). Each sample compiles its one `main()` file
together with any sibling helper translation units in the same folder.

## Notes

- The samples use `std::erase_if` and `std::sort` so the extracted logic does something
  concrete and deterministic (drop empty blobs, sort by size descending) that is easy to
  assert against.
- The **problem** sample deliberately *passes* its checks: the point is not that the
  workarounds fail to run, but that they couple tests to implementation details or bake
  test knowledge into production code.
- Choose the **free function** when the logic is stateless, and the **extracted class**
  when it owns state — both restore direct testability and improve encapsulation.

## Related

→ Guideline 1 (manage dependencies) and Guideline 2 (Design for Change) motivate *why*
testability matters. → Guideline 3 (Separate Interfaces) and the SRP discussion explain
*why* extracting the function is the right separation of concerns.
