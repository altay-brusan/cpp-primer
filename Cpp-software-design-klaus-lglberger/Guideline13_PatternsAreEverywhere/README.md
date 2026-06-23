# Guideline 13 — Design Patterns Are Everywhere

> **Concern:** Design patterns are neither outdated nor obsolete. Any kind of
> abstraction, and any attempt to decouple software entities to gain flexibility
> and extensibility, is very likely a known design pattern. The C++ Standard
> Library is full of them — once you learn the *intent* of each pattern, you start
> recognizing them everywhere.

*This is mostly a conceptual guideline, grounded in concrete Standard Library
examples. The folder ships one short runnable demo plus this documentation.*

## The idea

Some people claim design patterns are a relic of object-oriented programming, a
language-specific idiom, or tied to one particular implementation — and therefore
obsolete. The book pushes back hard: patterns are not about OOP, not about dynamic
polymorphism, not about a single language or implementation. They are about
**intent** — naming a recurring way to introduce an abstraction and decouple
software. By that measure they are everywhere, and the Standard Library proves it.

The book's headline example is the `std::pmr` (polymorphic memory resource)
allocator facility. A few lines of code that "don't look like they need any design
pattern" actually rest on **at least four** (five if you count Singleton):

```cpp
#include <array>
#include <cstddef>
#include <memory_resource>
#include <string>
#include <vector>

std::array<std::byte, 1000> raw;                 // uninitialized scratch buffer
std::pmr::monotonic_buffer_resource buffer{
    raw.data(), raw.size(), std::pmr::null_memory_resource() };
std::pmr::vector<std::pmr::string> strings{ &buffer };
strings.emplace_back("String longer than what SSO can handle");
```

No dynamic memory is used: every allocation is served from the byte array. And to
make that work, the facility quietly combines several patterns.

## Patterns hiding in `std::pmr`

| Pattern | Where it appears in the example |
|---------|---------------------------------|
| **Template Method** (via the NVI idiom) | `std::pmr::memory_resource` exposes public `allocate()` / `deallocate()` / `is_equal()` that forward to private virtuals `do_allocate()` / `do_deallocate()` / `do_is_equal()`. The public side is the fixed skeleton; derived classes fill in the steps. |
| **Decorator** | Passing `null_memory_resource()` as the backup allocator to `monotonic_buffer_resource` *wraps and extends* one allocator with another. Allocators can be layered into a full memory subsystem this way. |
| **Adapter** | `std::pmr::vector` and `std::pmr::string` are type aliases that plug a `std::pmr::polymorphic_allocator` into the regular containers, gluing the classic static allocator interface to the new dynamic `memory_resource` interface. |
| **Strategy** | Exposing the allocator as a template argument lets you customize *how* a container allocates from the outside — a static form of Strategy, the same intent as customizing an algorithm. |
| **Singleton** | `null_memory_resource()` returns a pointer to a single static-storage-duration object, so there is at most one instance of that allocator. |

## More patterns across the Standard Library

The book's broader point: there are *hundreds* of pattern examples in the Standard
Library. A few you already use daily:

- **Iterator** — `begin()` / `end()` and every algorithm that walks a range. The
  iterator decouples traversal from the container's storage.
- **Strategy** — a callable handed to an algorithm to customize one step, e.g. the
  comparator in `std::sort`, the predicate in `std::find_if`, or the binary
  operation in `std::accumulate`.
- **Type Erasure** — `std::function` and `std::any` store any conforming type
  behind one fixed value-type interface, with no common base class required.
- **Factory** — `std::make_unique` and `std::make_shared` create an object and
  hand back an owning handle, hiding the construction details.
- **Decorator** — `std::ranges` view adaptors (`views::filter`, `views::transform`,
  `views::take`, ...) wrap a range and layer behavior on top of it, composably.
- **Adapter** — the container adaptors `std::stack`, `std::queue`, and
  `std::priority_queue` adapt an underlying container to a narrower interface.

## Why it matters

If almost every abstraction is some pattern, then knowing patterns is not academic
trivia — it is shared vocabulary and a catalog of *intents*. Recognizing that a
problem calls for "Strategy" or "Decorator" lets you reuse a proven decoupling and
communicate the design in one word. Conversely, reaching for a pattern by **intent**
(not by its textbook implementation — see Guideline 12) keeps you from
over-engineering.

## Guideline (book summary)

- Understand that any kind of abstraction and any attempt to decouple likely
  represents a known design pattern.
- Learn about the different design patterns and understand their intent to decouple.
- Apply design patterns based on their intent whenever necessary.

## This folder

| Path | What it shows |
|------|---------------|
| `01_PatternsInTheSTL/main.cpp` | One self-contained program that demonstrates four Standard Library patterns in action — Iterator, Strategy, Type Erasure, and Factory — each labeled with the pattern it represents. |

Build (MSVC, C++23):

```
cl /std:c++latest /W4 /EHsc 01_PatternsInTheSTL\main.cpp
```

## Related

→ Guideline 11 (Understand the Purpose of Design Patterns) and Guideline 12 (Beware
of Design Pattern Misconceptions) set up *what* a pattern is and *what it is not*;
this guideline shows they are already all around you.
