# Guideline 30 — Apply Prototype for Abstract Copy Operations

> **Concern:** You hold only a pointer-to-base and want an *exact* copy of
> whatever concrete object it refers to — but you don't know its type. Copying
> through the base **slices**: it keeps the base sub-object and silently drops
> the derived part. The **Prototype** design pattern restores virtual copying
> with a `clone()` that each derived type overrides to reproduce itself.

## The idea

The book's example is an `Animal` hierarchy. Dolly the `Sheep` is reachable only
through an `Animal*`. We want another Dolly, but we "don't even know that we are
dealing with a `Sheep`. It could be any kind of animal" — an **open set of
types**. Copying via the base copy constructor would copy just the `Animal`
part: slicing.

Prototype's intent (Gang of Four): *"Specify the kind of objects to create using
a prototypical instance, and create new objects by copying this prototype."* In
C++ this is a **virtual `clone()`** in the base, commonly returning a
`std::unique_ptr<Base>`. Each derived class overrides it to copy-construct
itself:

```cpp
std::unique_ptr<Animal> Sheep::clone() const {
    return std::make_unique<Sheep>(*this); // reuse our own copy constructor
}
```

`clone()` is pure virtual, so every concrete type must supply it and — per the
LSP — must return a faithful copy of its own dynamic type. It reuses the class's
own copy constructor (DRY: still correct as members are added). It does **not**
hide the special member functions; it merely *adds* a way to perform virtual
copying. Ownership comes back as a `std::unique_ptr`, so there is no manual
`delete` and no slicing.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_Problem_Slicing` | Copying a polymorphic object through a **base value** slices it: the copy compiles and runs (slicing is well-defined) but loses the dynamic type and the derived state. A `std::vector<Animal>` slices every element on insertion. |
| 02 | `02_Solution_Clone` | A virtual `clone()` returning `std::unique_ptr<Animal>`; `Sheep` and `Dog` each override it. Cloning a prototype, and cloning a `std::vector` of base pointers, reproduces every element's true dynamic type and state — no slicing. |

Each sample is one self-contained `main.cpp`; `main()` performs the copy so the
difference is visible in the output.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 30

# Verify every sample compiles (MSVC, /std:c++latest /W4):
./run.ps1 -Verify -Guideline 30
```

Standard library only; no cross-folder includes. Each folder builds on its own.

## Notes

- **When Prototype is needed.** Only when you must copy through an abstraction —
  an **open set** of derived types reached via pointer-to-base — and ordinary
  copy construction would slice. The `clone()` name is almost a keyword for it.
- **Value semantics often avoids it.** The book stresses there is *no value
  semantics variant* of Prototype, but there usually doesn't need to be: with a
  **closed** set of types, a `std::variant<Dog, Cat, Sheep>` copies correctly
  with its ordinary copy constructor — no `clone()` required. A value-based
  hierarchy is simpler and more comprehensible, so prefer it when you can; reach
  for Prototype only when the open-set, reference-semantics setup forces it.
- **Costs.** Prototype lives in the realm of reference semantics: it pays for
  pointer indirection and (usually) a heap allocation per copy. Acceptable for
  the ability to copy an abstract entity, but a real reason to prefer value
  types where the design allows.

## Related

→ Guideline 22 (Prefer Value Semantics over Reference Semantics) is the reason
to avoid Prototype when possible. → Guideline 6 (Adhere to the Expected Behavior
of Abstractions) is why `clone()` must return a faithful copy. → Guideline 33
(Optimization Potential of Type Erasure) revisits avoiding the allocation.
