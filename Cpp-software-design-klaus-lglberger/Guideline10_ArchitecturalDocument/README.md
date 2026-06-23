# Guideline 10 — Consider Creating an Architectural Document

> **Concern:** An architecture is only as strong as the *shared understanding*
> behind it. Without a single document that captures the big-picture structure and
> the fundamental decisions, that understanding lives only in people's heads — where
> it drifts, diverges, and walks out the door when they leave.

*This is a conceptual guideline; the book presents no code for it, so this folder
is documentation only.*

## The idea

Start with one simple question: **do you have an architectural document?** Any plan
or description that summarizes the major points and fundamental decisions of your
architecture, that shows the high levels, the low levels, and the dependencies
between them?

Many teams answer "no" and justify it with *"We're Agile, we can change things
quickly!"* The book pushes back hard on this. The point of Agile is **not** the
ability to change things quickly — the point of Agile is to get **quick feedback**.
The whole process is built around fast feedback loops: business practices (planning,
small releases, acceptance tests), team practices (collective ownership, CI,
stand-ups), and technical practices (TDD, refactoring, pair programming). But quick
feedback only tells you that *something is broken*. You gain the ability to actually
change software quickly and safely only through **good software design and
architecture** — those are what save you the Herculean effort of change.

## Architecture is a shared understanding

The book grounds the document in Ralph Johnson's definition of architecture:

> In most successful software projects, the expert developers working on that project
> have a shared understanding of the system design. This shared understanding is
> called 'architecture.'
> — Ralph Johnson

If architecture *is* the shared understanding of the codebase — the global vision —
then a few uncomfortable questions follow. How many developers are on your team? Are
you certain all of them are familiar with the architecture **in your head**? That
they share the same vision and pull in the same direction?

Almost certainly not. Every developer has different experiences, slightly different
terminology, and sees the code slightly differently. Those small differences in the
*current* understanding lead to differences in the *future* vision. Over a short
period this is invisible; over the long run it surfaces as surprises,
misunderstandings, and misinterpretations.

This is exactly the purpose of an architectural document: **one common document that
unifies the ideas, visions, and essential decisions in one place** — helping to
maintain and communicate the state of the architecture, and to avoid
misunderstandings.

## Why document it — preserving decisions

A document also **preserves** ideas, visions, and decisions against the loss of
people. Imagine one of your leading architects — one of the brains behind the
design — leaves the organization. Without a record of the fundamental decisions,
that departure also means a loss of essential information about the codebase. The
consequences cascade:

- You lose **consistency** in the architectural vision.
- You lose the **confidence** to adapt or change architectural decisions.
- No new hire can replace that knowledge, and no one can extract it all from the
  code.
- The code becomes more rigid, more "legacy," which tempts the team toward rewriting
  large parts — what Joel Spolsky called *"the single worst strategic mistake that
  any company can make,"* because new code initially lacks the accumulated wisdom of
  the old.

The book draws an analogy to construction: a building site does not even **start**
without a plan that everyone agrees to. Without one, you get the classic argument —
*"I said the garage should be to the left of the house!" "But I built it to the
left." "Yes, but I meant **my** left, not your left!"* A shared, agreed-upon plan is
precisely what prevents this.

## What goes in it — and what doesn't

A common objection: *"such a document is so much work, and all the information is in
the code anyway, and the document goes out of date so quickly!"* The book's answer:
not if you do it properly.

An architectural document should **not** go out of date quickly, because it should
primarily reflect the **big picture**:

- The overall structure of the system.
- The connections between the key players.
- The major technological decisions.

It should **not** contain the little details that change very often — those genuinely
do live in the code, which contains all the details and thus represents the ultimate
truth. But code does not help when the information is hidden from plain sight and
requires an *archaeological effort* to extract. The big-picture items, by contrast,
are not expected to change. (Of course, "not expected to change" doesn't mean they
*won't* — software is, after all, expected to change.)

## Getting started — start small

Creating an architectural document sounds like an enormous amount of work, and the
book acknowledges that. The advice is simply to **get started somehow**:

- You don't have to document the architecture in all its glory at once.
- Begin with only the most **fundamental structural decisions**.
- Over time, add more and more architectural information, documenting and
  accumulating established wisdom for the whole team.

This is also where **architecture decision records** belong in spirit: capturing the
essential decisions — what was decided and why — so the reasoning survives independently
of any one person. The document becomes the team's shared, growing body of wisdom.

## Use tools to test architecture against reality

A document of fundamental structural decisions is not just prose — it can be
**machine-checkable**. Some tools can take your documented architectural boundaries
and compare your *assumed* architectural state against the *actual* state of the
code, flagging where real dependencies violate the intended structure. The book names
the **Axivion Suite** (define architectural boundaries between modules; the tool
checks that the dependencies are upheld) and **Sparx Systems Enterprise Architect** as
examples. This puts architecture on the same footing as a CI environment, automated
tests, and static analysis.

## Keeping it alive

*"But how do I keep this document up to date?"* You do have to maintain it —
integrate new decisions, update old ones. But because it should contain only the
aspects that **do not change often**, there is no need to constantly touch and
refactor it.

The book's suggestion: schedule a short meeting of the senior developers every one or
two weeks to discuss whether and how the architecture has evolved. That is enough to
keep it current, and it makes it hard for the document to become a bottleneck.

Think of the document as a **bank deposit safe**: it is invaluable to have all the
accumulated decisions of the past secured for when you need them — but you wouldn't
open it every single day.

## Guideline (book summary)

- Understand that an architectural document serves the purpose of **maintaining and
  communicating** the current state of the architecture.
- Recognize that the benefits of having an architectural document by far outweigh the
  risks and efforts; consider it an **essential part of any project**, as important as
  a CI environment or automated tests.
- Keep it focused on the **big picture** — overall structure, key connections, major
  technological decisions — not the fast-changing details.
- **Use tools** to support and help you test the current state of your architecture
  against the expected state.

## Related

→ Guideline 1 (Importance of Software Design) introduces the architecture/design/
implementation levels this document captures. → Guideline 2 (Design for Change) and
the dependency-management guidelines explain *what* the big decisions are about.
