# Guideline 1 — Understand the Importance of Software Design

> **Concern:** What actually makes a C++ project succeed or fail is not its
> features but its **structure**. Software design — the art of managing
> dependencies and abstractions — is the foundation of maintainable software.

*This is a conceptual guideline; the book presents no code for it, so this folder
is documentation only.*

## The idea

If you ask which code properties matter most, you say *readability, testability,
maintainability, extensibility, reusability, scalability*. But how you get them is
**not** by reaching for C++ features (RAII, lambdas, modules, …). Features are not
software design.

- **Features are not the differentiator.** A project can succeed on an old C++
  standard using a small subset of features. What determines success is the overall
  **structure**: how easily you can change, extend, and test the code, and how far it
  can scale before it collapses under its own weight.
- **Change is the one constant.** The reason a "2-point" ticket explodes into a
  week-long, risky modification is almost always one word: **dependencies**. As Kent
  Beck put it, *"Dependency is the key problem in software development at all scales."*
- **Necessary vs. artificial dependencies.** Some coupling is unavoidable (code must
  work together). But we also introduce *artificial* dependencies by accident — and
  those are what make software hard to understand, change, extend, and test. The
  primary task of a developer is to keep artificial dependencies to a minimum.
- **Definition.** *Software design is the art of managing interdependencies between
  software components. It aims at minimizing artificial (technical) dependencies and
  introduces the necessary abstractions and compromises.* It's an art, not a science —
  the honest answer to most design questions is *"it depends."*

## The three levels of software development

| Level | Deals with | Examples |
|-------|-----------|----------|
| **Software Architecture** | The big, hard-to-change decisions; large entities (modules, components) | client-server, microservices |
| **Software Design** | Interaction & dependencies of classes/functions; the tactics | Visitor, Strategy, Decorator |
| **Implementation Details** | How a solution is coded (features, memory, exception safety, performance) | `std::make_unique`, RAII, copy-and-swap |

The boundary between **architecture** and **design** is *fluid* — both manage
dependencies via abstractions; architecture is the strategy, design is the tactics.

- **Abstraction vs. encapsulation:** abstraction solves *design-level* problems (it
  decouples); encapsulation solves *implementation-level* problems (it hides detail).
  RAII is encapsulation, not abstraction — it doesn't decouple, it localizes.
- **Idioms** are language-specific patterns. Most C++ idioms (RAII, copy-and-swap) are
  *implementation* patterns, but a few — **NVI** (Template Method) and **Pimpl**
  (Bridge) — are *design* patterns that introduce abstraction and decouple.

## Why we over-focus on features

Three reasons: there are *so many* features that we must spend time on idiomatic use;
we put the *wrong expectations* on features (e.g. C++20 modules can reveal structural
flaws but cannot fix your design); and features are simply *easier* to explain than
design — feature questions have clear answers, design answers are "it depends."

## Guideline (book summary)

- Treat software design as an essential part of writing software.
- Focus less on C++ language details and more on software design.
- Avoid unnecessary coupling and dependencies to make software adaptable to change.
- Understand software design as the art of managing dependencies and abstractions.
- Consider the boundary between software design and software architecture as fluid.

## Related

→ Guideline 2 (Design for Change) makes "dependencies" concrete with the *Document*
example. → Guideline 3 (Separate Interfaces) and Guideline 5 (Design for Extension)
build on it.
