# Guideline 11 — Understand the Purpose of Design Patterns

> **Concern:** A design pattern is a **proven, named solution** to a recurring
> design problem, expressing an **intent to decouple** by introducing an
> **abstraction**. It lives at the *software design* level — it is about managing
> dependencies, **not** about a specific implementation, library, feature, or
> programming language.

*This is a conceptual guideline; the book presents no code for it (aside from a
single counter-example signature), so this folder is documentation only.*

## The idea

Design patterns are not new — they have been around at least since the Gang of
Four (GoF) published their book in 1994 — and their value is acknowledged across
the industry. Yet many **misconceptions** persist, especially in the C++
community. To use patterns productively, you first have to understand *what a
design pattern is*. A design pattern:

- **has a name**,
- **carries an intent**,
- **introduces an abstraction**, and
- **has been proven**.

## What a design pattern is — the four properties

### 1. A design pattern has a name

This sounds obvious, but the name is a *fundamental* property. A shared name lets
two developers communicate at a very high level and exchange a lot of information
with very few words. Saying *"I would use a **Visitor** for that"* tells your
colleague both what you believe the real problem is and what kind of solution you
propose. A whole conversation about how a codebase should evolve can be carried by
just three words — *Visitor*, *Strategy*, *Decorator* — that would otherwise take
several paragraphs of explicit detail to express. This precise communication is
possible *only* if everyone shares the same understanding of the patterns, which is
exactly why it matters to know them and talk about them.

### 2. A design pattern carries an intent

The name conveys the **intent**. When you use a pattern's name you implicitly
state what you consider the *problem* and what you see as the *solution*. Crucially,
in that kind of conversation you are **not** talking about implementation: not about
implementation details, not about features, not about any particular C++ standard —
not even about any particular programming language. The name tells you about the
**structure** proposed, about how dependencies will be managed, and about how the
system is expected to evolve. That is the intent.

This is why **structure alone does not identify a pattern**. Structurally, the
*Strategy*, *Command*, and *Bridge* patterns look almost identical, yet their intent
differs, so they solve different problems. And for any given pattern there are
almost always many different implementations to choose from — the pattern does not
imply one.

### 3. A design pattern introduces an abstraction

A pattern always reduces dependencies by introducing **some kind of abstraction**.
It is always concerned with managing the interaction between software entities and
**decoupling** pieces of software.

- **Strategy** introduces an abstraction (the `Strategy` base class) that decouples
  the user (the high-level `Context`) from the implementation details (the concrete
  strategies in the low level).
- **Factory Method** introduces the `Product` and `Creator` abstractions (high
  level) to decouple from the creation of specific products (`ConcreteProduct`,
  `ConcreteCreator`, low level). It qualifies because it has a name, the intent to
  decouple, and it introduces abstractions.

The abstraction need **not** be a base class. It can be introduced in many ways —
for example via templates or simple function overloading. Again: a design pattern
does **not** imply any specific implementation.

### 4. A design pattern has been proven

A pattern is not just any clever solution. The GoF collected only solutions that
were *commonly used* across different codebases to solve the same problem (often
with different implementations). A solution must demonstrate its value several times
before it earns the status of a pattern.

## Design pattern vs. implementation pattern (the `std::make_unique` counter-example)

In the C++ community `std::make_unique()` is often called a *factory function*,
which gives the misleading impression that it is an instance of the *Factory Method*
design pattern. It is **not**.

```cpp
namespace std {
  template< typename T, typename... Args >
  unique_ptr<T> make_unique( Args&&... args );
}
```

A design pattern decouples by introducing an abstraction that lets you **customize
and defer** implementation details. The intent of Factory Method is to introduce a
*customization point* for object instantiation. `std::make_unique()` provides no
such customization point: you always get a `std::unique_ptr` to exactly the type you
asked for, always created via `new`:

```cpp
// This will create a 'Widget' by means of calling 'new'
auto ptr = std::make_unique<Widget>( /* some Widget arguments */ );
```

Because it offers no way to customize that behavior, it cannot reduce coupling
between entities and therefore cannot serve the purpose of a design pattern.

It *is* still a recurring solution to a specific problem — so it is a **pattern**,
but an **implementation pattern**, not a design pattern. It encapsulates an
implementation detail (generating a `Widget` instance) but does not *abstract* from
*what* you get or *how* it is created. It belongs to the **Implementation Details**
level, not the **Software Design** level (see Guideline 1, Figure 1-1).

The contrast is the whole point: introducing abstractions is the key to decoupling
and to designing for change and extension. There is no abstraction in
`std::make_unique` — you cannot extend, overload, or specialize it. Factory Method
abstracts from both *what* is created and *how* (including actions before and after
instantiation), so you can add new factories later **without changing existing
code**. That is what makes one a design pattern and the other only an implementation
pattern.

## Patterns, implementation patterns, and idioms

- **Design pattern** — proven, named, intent to decouple, introduces an abstraction;
  lives at the *software design* level (manages dependencies).
- **Implementation pattern** — a recurring solution that encapsulates an
  implementation detail but introduces no decoupling abstraction (e.g.
  `std::make_unique`); lives at the *implementation details* level.
- **Idiom** — a language-specific pattern. Most C++ idioms are *implementation*
  patterns, though a few (NVI, Pimpl) are *design* patterns (see Guideline 1).

## Why the name matters

The name is the carrier of intent and the medium of design-level communication. It
lets a team reason about *structure* and *evolution* rather than implementation
trivia, and it keeps discussions free of any particular feature, standard, or
language. Just as "Design" should be used precisely to mean the art of managing
dependencies and decoupling (Guideline 1), the term "Design Pattern" should be used
accurately and on purpose.

## Guideline (book summary)

- Understand that design patterns are **proven, named solutions** with an **intent
  to decouple**.
- Realize that design patterns introduce some kind of **abstraction**.
- Keep in mind that design patterns are targeted at **software design**, i.e., they
  help to **manage dependencies**.
- Be aware of the difference between **design patterns** and **implementation
  patterns**.

## Related

→ Guideline 1 (Importance of Software Design) defines the three levels and the
design-vs-implementation distinction this guideline builds on. → Guideline 12
(Beware of Design Pattern Misconceptions) corrects further myths. → The Strategy,
Factory Method, Visitor, Decorator, and Bridge patterns named here are explored in
depth in the following chapters.
