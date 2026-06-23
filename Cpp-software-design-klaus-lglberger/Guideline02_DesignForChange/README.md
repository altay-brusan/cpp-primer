# Guideline 2 — Design for Change

> **Concern:** Software is *expected* to change. The thing that makes change slow
> and risky is **coupling** — especially *artificial* coupling between unrelated,
> orthogonal aspects. Separate concerns (SRP) and avoid duplication (DRY) so that
> each kind of change happens in **exactly one place**.

## The idea

Iglberger illustrates the point with the classic abstract **`Document`** class. It
*looks* like a great all-in-one base class — it can export to JSON, it can serialize
itself to bytes — but that is precisely the trap. JSON export and serialization are
**orthogonal aspects** that change for different reasons, and bundling them into the
document interface manufactures dependencies nobody asked for:

- `exportToJSON()` forces every derived class to depend on a particular JSON library;
  swapping libraries (or even just its argument types leaking into the signature)
  ripples through the whole hierarchy and its callers.
- `serialize()` couples documents to a `ByteStream` format **and** to a global
  `DocumentType` enum, so adding one new document type touches code every other
  document depends on.
- A low-level `User` that only wants to *read* a document is now transitively coupled
  to JSON and serialization — an **artificial**, not intrinsic, dependency.

The fix is **separation of concerns** (the Single-Responsibility Principle): strip
`Document` back to the fundamental document operations and extract JSON and
serialization into their own **variation points** — the one place each kind of change
is expected. A second, related lever is **Don't Repeat Yourself (DRY)**: the `Item`
hierarchy that hardcodes a `15%` tax rate in every class shows that duplicated
knowledge means a codebase-wide edit when the rate changes; keep it in one place.
(The book also cautions against *premature* separation — use SRP/DRY to achieve
maintainability, not as goals in themselves: YAGNI.)

## Samples

| # | Folder | What it shows |
|---|--------|---------------|
| 1 | `01_Problem_Coupling` | The over-loaded `Document` that mixes data, JSON export, and serialization — compiles and runs, but couples three orthogonal concerns and violates the SRP. |
| 2 | `02_Solution_SRP` | `Document` slimmed to its core; JSON and serialization extracted into separate components (variation points) so each change lands in one place. |
| 3 | `03_DRY_TaxRate` | The `Item` hierarchy with the tax rate as a single source of truth, illustrating Don't Repeat Yourself (vs. duplicating `* 1.15` everywhere). |

## Build & run

From the repository root, use the launcher:

```powershell
# interactive: pick a sample of Guideline 2
./run.ps1 -Guideline 2

# compile-check every sample of this guideline
./run.ps1 -Verify -Guideline 2

# build + run a specific sample (1, 2, or 3)
./run.ps1 -Guideline 2 -Sample 2
```

Each sample is a self-contained folder: one `.cpp` with `main()` plus any sibling
headers/`.cpp` helpers in the same folder. Compiled with MSVC, C++23
(`/std:c++latest`).

## Notes

- **Standard library only.** The book uses a real third-party JSON library; here a
  tiny inline `JsonValue` / `std::string` stub stands in. The *design point* —
  artificial coupling to a formatting decision — is preserved; only the include is gone.
- The **problem** sample is intentionally bad *design*, not bad *syntax*: it builds
  and runs so the coupling smell is visible.
- In `02_Solution_SRP` the variation points are free functions in `Components.cpp`:
  swapping the JSON "library" edits `exportToJson()` only; changing the byte format
  edits `serialize()` only; neither touches the `Document` hierarchy.
- The book points forward to design patterns that formalize these separations —
  **Strategy** (Guideline 19), **Visitor** (Guideline 16), **External Polymorphism**
  (Guideline 31), and **Decorator** (Guideline 35) for the configurable-tax problem.
