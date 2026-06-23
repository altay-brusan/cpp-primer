# Guideline 22 — Prefer Value Semantics over Reference Semantics

> **Concern:** The classic GoF style is built on inheritance hierarchies and
> therefore on **reference semantics** — pointers, references, pointer-to-base
> polymorphism, shared mutable state. That style forces the reader to reason by
> hand about ownership, null-ness, aliasing, and lifetime, which makes code
> harder to understand and easier to break. **Value semantics** — regular value
> types, deep copies, `std::variant`, `std::optional`, returning by value — is
> simpler to reason about, safer, and often faster, because a value owns its
> content, a copy is independent, and `const` is total.

## The idea

The book contrasts two ways of writing the same code. **Reference semantics**
works primarily through pointers and references; the name carries a negative
connotation because of the dangers it invites. The book shows two famous traps:

- A `const std::span<int>` over a `std::vector<int>` still lets you **mutate**
  the underlying array — `const` binds the *handle*, not the referenced data —
  and the span **dangles** the moment the vector reallocates. A span is a
  pointer in disguise, so it inherits every pointer hazard.
- The erase–remove idiom passing `*pos` (a reference into the very vector being
  modified) removes the **wrong** elements, because the referenced value changes
  underneath the algorithm.

Both are symptoms of the same thing: *"references, and especially pointers, make
our life so much harder."* Pointers raise the recurring questions *is it valid or
`nullptr`? who owns it? is the referenced value still alive?* Smart pointers fix
*ownership*, but as the book puts it they are *"only a fix for the holes that
reference semantics has torn in the fabric of our ability to reason about code."*

**Value semantics** is the Modern C++ alternative. A `std::vector` copy is a deep,
independent copy; a `const` vector is const all the way down; a change is local
and cannot surprise another part of the program. The book replaces the
pointer-to-base hierarchy with `std::variant` (values dispatched by `std::visit`)
and replaces a `std::unique_ptr<int>` / output-parameter result with
`std::optional<int>` returned by value: *"semantically clear, understandable, and
efficient,"* with no allocation and no lifetime management. It can even be faster,
thanks to a contiguous layout and fewer indirections.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_Problem_ReferenceSemantics` | A pointer-heavy design: `vector<unique_ptr<Shape>>` polymorphism, non-owning raw aliases (shared mutable state — a write through one alias is visible through another), and a `const std::span` that still mutates its vector. The dangling cases (reallocation, `clear()`) are described in comments only and never executed, so it compiles and runs safely. |
| 02 | `02_Solution_ValueSemantics` | The value-based twin: `std::variant<Circle, Square>` held by value and dispatched with `std::visit`, deep independent copies (mutating a copy leaves the original untouched), a `const` variant that cannot be mutated through any path, and `std::optional<int>` returned by value for fallible parsing — no ownership, no `nullptr`, no lifetime to manage. |

Each sample is a single self-contained `main.cpp` using the standard library
only; its `main()` prints results so the contrast is visible at runtime.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 22

# Verify every sample compiles (MSVC, /std:c++latest /W4):
./run.ps1 -Verify -Guideline 22
```

## Notes

- **Reference semantics raises questions value semantics never asks.** Ownership,
  validity (`nullptr`), aliasing, and lifetime all become manual obligations the
  moment a design works through pointers and references.
- **`const` differs.** A const *value* is fully const; a const *reference type*
  (pointer, `std::span`, `std::string_view`) only freezes the handle, not the
  pointed-to data. The Problem sample makes this visible.
- **Aliasing is the subtle one.** Two handles to one object mean a write *here*
  is silently a write *there*. A value copy is independent, so changes stay local
  — which is exactly what compilers exploit for optimization.
- **`std::variant` over a class hierarchy.** A closed set of value types in one
  contiguous container removes the heap allocations, the virtual indirection, and
  the pointers, while `std::visit` keeps the polymorphic dispatch.
- **`std::optional` over output parameters or `unique_ptr` returns.** A result
  returned by value is semantically clear, allocation-free, and lifetime-free —
  the most natural way to return a result is *as the return value*.
- **Cost myth.** Copies are only expensive if they actually happen; copy elision,
  move semantics, and judicious pass-by-reference keep value semantics efficient
  — and the better memory layout can make it the *faster* choice.
- **Use references deliberately.** The book is not banning pointers or reference
  parameters — `std::span` and `std::string_view` are excellent *function
  arguments*. The advice is to prefer value semantics for design, and to reach
  for non-owning reference types consciously, aware of their lifetime demands.

## Related

→ Guideline 19 (Strategy) and Guideline 21 (Command) present the GoF,
reference-semantics form these ideas refine. → Guideline 23 (Prefer a
Value-Based Implementation of Strategy and Command) applies this guideline
directly to those patterns. → Guideline 17 (`std::variant` for Visitor) is the
performance precedent the book cites here.
