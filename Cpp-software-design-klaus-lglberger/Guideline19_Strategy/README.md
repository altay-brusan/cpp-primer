# Guideline 19 — Use Strategy to Isolate How Things Are Done

> **Concern:** *How* something is done — how a shape is drawn — is a **variation
> point**. Bake that detail into the type via inheritance and the design becomes
> rigid: the class count explodes along every axis of change. The **Strategy**
> design pattern extracts the varying behavior into a separate, injectable object
> so it can vary independently of the type and be changed or extended **without
> modifying the type**.

## The idea

The book uses a 2D graphics tool. A `Shape` base class offers a pure virtual
`draw()`, and the team implements `draw()` directly inside `Circle` and `Square`.
The moment a second backend is needed (OpenGL versus a console), they reach for
inheritance — `OpenGLCircle`, `ConsoleCircle`, `OpenGLSquare`, … — and the
hierarchy grows as *shapes × backends*. Add a second varying operation such as
`serialize()` and it multiplies again into `OpenGLProtobufCircle` and friends.
This violates the **Single Responsibility Principle**: the *how* (drawing detail)
is welded to the *what* (the geometric type). As the book puts it,
*"inheritance is rarely the answer."*

The fix is to **identify the drawing aspect as a variation point and extract
it** — the intent of Strategy: *"Define a family of algorithms, encapsulate each
one, and make them interchangeable. Strategy lets the algorithm vary
independently from clients that use it."*

- **Runtime Strategy (base class + injection).** A `DrawStrategy` abstraction is
  injected into each shape through its constructor (**dependency injection**).
  The shape's `draw()` merely forwards to the strategy. Switching backend is a
  local change; a setter even swaps it at runtime. Crucially, the book warns that
  a **single shared** `DrawStrategy` artificially couples all shapes (adding a
  `Triangle` would force `Circle` and `Square` to recompile — an Interface
  Segregation violation). The remedy is **one strategy interface per shape**,
  best expressed as a class template `DrawStrategy<T>`.
- **Compile-time Strategy (policy-based design).** The same intent in static
  polymorphism: inject the behavior through a **template parameter**, the way
  `std::sort`'s comparator and `std::unique_ptr`'s `Deleter` do. No virtual call,
  no allocation — at the cost of a distinct type per policy and no runtime swap.

Per the book's caution: identify variation points early but do not over-engineer
— a Strategy should isolate **one** operation (or a small cohesive group), or you
re-introduce the SRP violation you set out to remove.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_Problem_Inheritance` | Drawing baked into the type via inheritance. A second backend forces `OpenGLCircle`/`ConsoleCircle`/… so the class count grows as *shapes × backends*; a shape cannot change its drawing at runtime and backend code cannot be shared. Compiles and runs. |
| 02 | `02_Solution_Strategy` | Runtime Strategy: a `DrawStrategy<T>` interface (one per shape, avoiding artificial coupling) injected by constructor. Backends switch locally, a setter swaps one at runtime, and a new `SvgCircleStrategy` is added touching no shape. |
| 03 | `03_Solution_PolicyBased` | Compile-time Strategy: the drawing policy is a template argument (`Circle<DrawPolicy>`), the static-polymorphism twin with no virtual call. A new `SvgStrategy` plugs in by adding one policy class. |

Each sample's `main()` builds shapes with strategies and draws them; the
solutions add a brand-new backend to show that extension touches no existing
shape or strategy.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 19

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 19
```

Each sample is a single self-contained `main.cpp` using the standard library
only; drawing backends are simulated with console output.

## Notes

- **Strategy isolates the HOW.** It extracts the implementation detail of an
  operation (how a shape is drawn) and makes it interchangeable, so behavior
  varies independently of the shape — the opposite end of the design space from
  Visitor, which isolates *what* operations exist.
- **Strategy vs. inheritance.** Inheritance bakes the variation into subclasses,
  exploding the hierarchy as *types × backends × operations* and freezing the
  behavior at construction. Strategy keeps the shape a simple primitive and lets
  the behavior be composed, swapped, reused, and extended.
- **One Strategy per operation.** A single shared `DrawStrategy` couples all
  shapes (an ISP violation); per-type interfaces (or `DrawStrategy<T>`) keep
  types decoupled so new shapes are still easy to add — the strength of OOP.
- **Strategy vs. Visitor.** Whichever you apply first fixes one axis of freedom:
  Strategy keeps *adding types* easy but *adding operations* hard; Visitor is the
  reverse. Choose based on how the code is expected to evolve.
- **Trade-offs.** The OO form costs a virtual indirection plus an allocation per
  strategy; policy-based design removes both but yields a distinct type per
  policy and no runtime swap. There is no silver bullet — *it depends*.

## Related

→ Guideline 5 (Design for Extension) sets up the OCP this pattern serves.
→ Guideline 15 (Addition of Types or Operations) frames the type-vs-operation
choice. → Guideline 16 (Use Visitor to Extend Operations) is Strategy's mirror
image. → Guideline 23 (Value-Based Strategy and Command) revisits this with value
semantics.
