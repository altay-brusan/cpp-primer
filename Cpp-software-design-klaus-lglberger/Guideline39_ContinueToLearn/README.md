# Guideline 39 — Continue to Learn About Design Patterns

> **Concern:** A book has a finite number of pages, but software design has none.
> The patterns covered here are *the most useful*, not *all of them*. To keep
> growing as a designer you must **keep learning patterns** — their intent, their
> trade-offs, and how they actually appear in real code.

*This is the closing, conceptual guideline of the book ("The Last Guideline").
It presents no code, so this folder is documentation only.*

## The idea

"That's it? There are so many more design patterns out there. We barely touched the
surface!" — and that is completely correct. The author had planned for many more
patterns until reality struck: there is only so much that fits into ~400 pages. But
those pages take you through the most important pieces of advice for *any* design,
**anywhere, anytime** in your career. Patterns are not a closed list you finish; they
are a discipline you keep practicing.

## The takeaway of the book

The general, pattern-independent advice you carry away:

- **Minimize dependencies.** Dealing with dependencies is the *core* of software
  design. Reduce the necessary ones and — primarily — eliminate the artificial ones.
  Pursuing this goal inevitably leads you to design patterns.
- **Separate concerns.** Possibly the single most important guideline in the book.
  Every design pattern, *without exception*, provides some way to separate concerns.
  What differs between patterns is *how* they do it — their **intent**, which is always
  unique even when their structure looks similar.
- **Prefer composition to inheritance.** The true strength of many patterns (Strategy,
  Bridge, Adapter, Decorator, External Polymorphism, Type Erasure) comes from
  composition; inheritance is then an *option* for extension, not the foundation.
- **Prefer a nonintrusive design.** Real flexibility comes from being able to *add*
  code rather than *modify* existing code. That is why Decorator, Adapter, External
  Polymorphism, and Type Erasure are such valuable tools.
- **Prefer value semantics over reference semantics.** Values keep code simple and
  away from `nullptr`s, dangling pointers, and lifetime dependencies. As `std::variant`
  and Type Erasure show, value semantics need not cost performance — it may even
  improve it.

You have also internalized **what a design pattern actually is**. A design pattern:
*has a name*, *carries an intent*, *introduces an abstraction*, and *has been proven*.
With that, you will no longer fall for false claims that some implementation detail is
a "pattern" — e.g. smart pointers (`std::unique_ptr`, `std::shared_ptr`) or factory
functions such as `std::make_unique()` are **not** design patterns.

## Patterns covered — and worth revisiting

The book already armed you with several of the most important, repeatedly useful
patterns:

| Pattern | When to reach for it |
|---------|----------------------|
| **Visitor** | Extend *operations* on a closed set of types (possibly via `std::variant`). |
| **Strategy** | Configure behavior and inject it from outside (aka policy-based design). |
| **Command** | Abstract over different kinds of operations, possibly undoable ones. |
| **Observer** | Observe state changes in some entity. |
| **Adapter** | Adapt one interface to another, nonintrusively, without changing code. |
| **CRTP** | A static abstraction free of virtual functions (when C++20 concepts aren't an option); also compile-time mixins. |
| **Bridge** | Hide implementation details and reduce physical dependencies. |
| **Prototype** | Create a virtual copy. |
| **External Polymorphism** | Add polymorphic behavior externally to promote loose coupling. |
| **Type Erasure** | External Polymorphism plus the advantages of value semantics. |
| **Decorator** | Nonintrusively add responsibilities to an object. |

## Patterns worth studying next

There are *many more* important and useful patterns the book did not have room for.
Among the classics worth getting to know are **Factory Method**, **Builder**,
**Facade**, and **Memento**, alongside the rest of the catalog of established design
patterns. For each new pattern, focus on:

- its **intent**, and
- its **similarities and differences** versus patterns you already know.

Remember: design patterns are about a **dependency structure**, not about
implementation details.

## How to keep learning

There are two complementary paths:

1. **Get to know more patterns.** Study their intent and how they relate to the
   patterns you already understand.
2. **Deepen your understanding of each pattern.** Experience their advantages *and*
   shortcomings firsthand by spotting them in the codebases you work on. You will find
   many — any serious attempt to manage and reduce dependencies is very likely the
   trace of a design pattern. **Design patterns are everywhere.**

## Guideline (book summary)

- Get to know more design patterns and understand their intent.
- Learn more about the advantages and disadvantages of each design pattern.
- Find design patterns in the wild to experience them hands-on.

## Related

→ This guideline ties back to *every* pattern guideline in the book — Visitor,
Strategy, Command, Observer, Adapter, CRTP, Bridge, Prototype, External Polymorphism,
Type Erasure, and Decorator — and back to Guideline 1 (Importance of Software Design),
which framed design as the art of managing dependencies and abstractions.
