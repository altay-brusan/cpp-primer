# Guideline 12 — Beware of Design Pattern Misconceptions

> **Concern:** Knowing what a design pattern *is* is only half the battle; you
> also need to know what a design pattern is **not**. A pattern is not a goal,
> not an implementation detail, not a language-specific idiom, and not bound to
> object-oriented programming or dynamic polymorphism. Misunderstanding any of
> these turns a useful tool into a source of complexity and frustration.

*This is a conceptual guideline; the book debunks myths rather than presenting a
single implementation, so this folder is documentation only.*

## The idea

A design pattern is the combination of a **name**, an **intent**, and some form of
**abstraction to decouple software entities** (see Guideline 11). Just as it's
important to understand that definition, it's important to recognize the
misconceptions that cluster around patterns. These myths arise because we rarely
talk about *design* and instead focus on features and language mechanics (see
Guideline 1). This guideline debunks the first three; the fourth ("patterns are
outdated") is handled separately in the next guideline.

- Some treat patterns as a **goal** and a guarantee of software quality.
- Some believe patterns are tied to a **particular implementation** and are
  therefore language-specific idioms.
- Some think patterns are limited to **object-oriented programming and dynamic
  polymorphism**.
- Some consider patterns **outdated or obsolete** (covered in the next guideline).

## Misconception 1 — "Design patterns are a goal"

**The myth.** Some developers are so infatuated with patterns that they try to
solve every problem with one, whether reasonable or not. There must be a reward
for using as many patterns as possible.

**The reality.** Design patterns are **not a goal — they are a means to achieve a
goal**. They may be part of the solution, but they are never the objective. As
Venkat Subramaniam puts it: if you wake up thinking *"What design pattern will I
use today?"*, that's a telltale sign you've missed the point. There is no medal
for cramming in patterns.

- Using a pattern should **decrease** complexity, not increase it. The code should
  become simpler, more comprehensible, and easier to change and maintain, because
  the pattern resolves dependencies and creates better structure.
- If a pattern leads to *higher* complexity and creates problems for other
  developers, it apparently isn't the right solution. Overuse breeds frustration,
  a bad reputation for patterns, and outright rejection of the idea of patterns.
- The point is **not** "don't use patterns" — it's "don't *overuse* them," just as
  you wouldn't overuse any other tool. It always depends on the problem: a hammer
  is great as long as your problem is nails; the moment it's screws, the hammer is
  an inelegant tool. Knowing *when not to* apply a pattern requires a firm grasp of
  its intent and structure.

## Misconception 2 — "Design patterns are about implementation details"

**The myth.** A pattern *is* a specific implementation, and thus more or less a
language-specific idiom. This is easy to believe because GoF patterns are usually
presented in an object-oriented setting with object-oriented examples, so the
implementation details get mistaken for the pattern itself.

**The reality.** Patterns are **not about implementation details, any particular
language feature, or any C++ standard**. The same pattern can be expressed in
fundamentally different ways. The book demonstrates this with the **Strategy**
pattern applied to drawing a `Circle`:

- **Classic OO version.** Implementing `draw()` directly inside `Circle` couples
  it to a graphics library (OpenGL, Metal, Vulkan, …) and violates the
  Single-Responsibility Principle (Guideline 2). The fix is to extract the *how to
  draw* decision behind a `DrawStrategy` base class — a variation point — and
  inject a concrete strategy from the outside (dependency injection). This factors
  out library dependencies, improves changeability and extensibility, and makes the
  design testable (e.g. a `TestStrategy`).
- **Template version.** The very same intent can be realized with a *template
  parameter* (`template< typename DrawStrategy > class Circle`). Now the decision
  happens at **compile time**: no base class, no virtual functions, no runtime
  decision, and one `Circle` type per concrete strategy — yet `Circle` is still
  decoupled from the graphics library. The trade-off is recompilation whenever the
  strategy changes.

Both implementations realize the **intent** of Strategy perfectly, which proves a
pattern is not restricted to a particular implementation or a specific form of
abstraction.

## Misconception 3 — "Design patterns are limited to OOP / dynamic polymorphism"

**The myth.** Because Strategy is a classic GoF pattern, it is an "object-oriented
pattern" that requires a base class and runtime (dynamic) polymorphism.

**The reality.** Patterns work **equally well for static polymorphism** and combine
naturally with C++ templates. The Standard Library is full of Strategy used
generically:

- **`std::accumulate`** (`<numeric>`) takes a fourth argument — the reduction
  operation (e.g. `std::plus<>{}`, `std::multiplies<>{}`). That argument injects
  *how* to reduce from the outside, so `accumulate` depends on no single
  implementation. That is exactly the intent of Strategy, expressed functionally
  rather than with inheritance. Without it, `accumulate` would be useful in very
  few cases; with it, the number of uses is endless.
- **Container allocators / comparators.** `std::vector<T, Allocator>` and
  `std::set<Key, Compare, Allocator>` let you customize memory allocation (and
  ordering) via *template arguments*. They define a family of algorithms,
  encapsulate each, and make them interchangeable independently of the container
  that uses them — Strategy again, this time via static polymorphism.

So patterns are **not limited to dynamic polymorphism** and **not limited to OOP**;
their intent serves functional and generic programming too. The book is careful to
add nuance: a *few* patterns do target OO-specific problems (e.g. **Visitor**,
**Prototype**), and a few are specific to other paradigms (e.g. **CRTP** and
**Expression Templates** for generic programming). Most patterns are not
paradigm-centric, but some are more specialized — and both kinds still share the
three defining traits: a name, an intent, and some form of abstraction.

## In summary

Design patterns are **not** language-specific idioms, **not** about a particular
implementation, and **not** confined to object-oriented programming or dynamic
polymorphism. They are focused entirely on the **intent to decouple software
entities** in a specific way — and they are a tool, not a trophy.

## Guideline (book summary)

- Consider design patterns as a tool to solve a design problem, **not as a goal**.
- Be aware that design patterns are **not limited to object-oriented programming**.
- Bear in mind that design patterns are **not limited to dynamic polymorphism**.
- Understand that design patterns are **not language-specific idioms**.

## Related

→ Guideline 11 (Understand the Purpose of a Design Pattern) defines the name +
intent + abstraction that this guideline defends. → Guideline 1 (Importance of
Software Design) explains *why* these misconceptions persist (we focus on features,
not design). → Guideline 2 (Design for Change) supplies the SRP motivation behind
the `Circle`/`DrawStrategy` refactoring. → The "patterns are outdated" myth is
debunked in the following guideline.
