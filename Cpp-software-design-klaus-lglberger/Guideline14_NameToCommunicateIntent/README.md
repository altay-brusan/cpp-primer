# Guideline 14 — Use a Design Pattern's Name to Communicate Intent

> **Concern:** A design pattern's name is a piece of **shared vocabulary**. Naming a
> class, function, or template parameter after the pattern it implements (`...Strategy`,
> `...Command`, `...Visitor`) communicates the *intent* of a solution instantly and
> improves readability. An arbitrary or — worse — a *wrong* name throws that meaning
> away and misleads the reader.

*This is a conceptual guideline; the book's only listing is a short illustration of
`std::visit`, so this folder is documentation only.*

## The idea

Every design pattern has a name, and that name expresses a clear, concise, and
unambiguous intent. The name carries meaning. By using the name of a design pattern you
can simultaneously express three things:

- **what the problem is** that you are solving,
- **which solution** you have chosen to solve it, and
- **how the code is expected to evolve**.

A good name carries more information than an arbitrary one. As the book stresses, *good
names always carry meaning — this is why they are so fundamentally important.* When the
name of a design pattern helps a reader understand the code in its specific context,
include it to express your intent.

## Pattern names as shared vocabulary

Terms like *Strategy*, *Command*, and *Visitor* carry meaning for every C++ programmer.
They are a common language: a single word stands in for a whole structure, a set of
expectations, and an evolution story that the reader already knows. Reaching for that
vocabulary lets you say a great deal with very little, and it ties your code to the body
of knowledge captured by the Gang of Four (GoF) patterns.

This is why naming with a pattern beats naming with a generic description — the generic
name describes a mechanic, the pattern name describes an *intent*.

## Naming after the pattern conveys intent

The book builds the point through Standard Library examples, each refining the previous one.

- **`accumulate()` — from mechanic to intent.** The standard signature names its third
  template parameter `BinaryOperation`. That communicates a fact (the callable takes two
  arguments) but **not** the intent. Renaming it `BinaryReductionStrategy` captures the
  intent clearly: the term *Reduction* says *what* it does, and *Strategy* says that the
  parameter enables **dependency injection** of the binary operation — it lets the caller
  specify *how* the reduction works. It solves the problem of **customization**.

  ```text
  template< class InputIt, class T, class BinaryOperation >          // a mere fact
  template< class InputIt, class T, class BinaryReductionStrategy >  // the intent
  ```

- **`for_each()` — Strategy vs. Command.** The pattern name also fixes the *expectations*.
  *Strategy* communicates that there are expectations on the operation: you may specify
  *how* the reduction works, but you cannot redefine *what* `accumulate()` does. When
  there are (nearly) **no** expectations on the operation — you can apply any unary
  operation at all — the right name is **Command**. So `for_each`'s callable is best read
  as a `UnaryCommand`. Choosing *Strategy* vs. *Command* is choosing which message to send.

- **`std::visit()` — the name *is* the pattern.** The function name refers directly to the
  **Visitor** design pattern and therefore states its intent outright: you can apply any
  operation to the closed set of types held in a `std::variant`, and you can extend the
  set of operations nonintrusively. The reader who knows the pattern knows the capability
  the moment they read the name.

## Pitfalls: wrong and empty names

- **Empty / arbitrary names mislead by omission.** A name like `BinaryOperation` is not
  wrong, but it leaves the intent unstated; the reader has to reconstruct it from the
  surrounding code. An arbitrary name forfeits the information a pattern name would have
  carried for free.
- **Wrong pattern names actively mislead.** Because a pattern name promises a specific
  structure and set of expectations, applying it to something that is *not* that pattern
  sends the reader a false signal. Calling something `...Strategy` when callers may
  redefine the whole behavior (a *Command* situation), or vice versa, communicates the
  wrong contract.
- **Naming is still hard.** Using a pattern name is not a license to stop thinking.
  Naming is genuinely difficult, and a name should *primarily* help understanding in a
  specific context. Only when a pattern name actually aids that understanding should you
  reach for it — do not bolt a pattern name onto code that does not implement the pattern
  just to sound sophisticated.

## Guideline (book summary)

- Use the name of a design pattern to communicate the **intent** of a solution.
- Use the name of a design pattern to improve **readability**.

## Related

→ Guideline 13 (the preceding sections) establishes *what a design pattern is* and that
patterns are everywhere — the basis for treating their names as vocabulary. → The Visitor
pattern (Chapter 4: Guidelines 15–18), the Strategy and Command patterns (Chapter 5,
including Guideline 19, "Use Strategy to Isolate How Things Are Done"), and the Bridge
pattern (Guideline 28) are the patterns whose names this guideline puts to work.
