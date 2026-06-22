/*
 * Chapter 12 - Concepts (1/6): Defining a Concept
 *
 * A *concept* (C++20) is a named compile-time predicate on template
 * parameters. The syntax is:
 *
 *     template <typename T>
 *     concept NameOfConcept = constant-expression-using-T;
 *
 * Here `Big` is true when `sizeof(T) > 4`. The expression has to be
 * usable at compile time and yield a `bool`.
 *
 * `static_assert(Big<long double>)` shows how to test a concept directly.
 * It's also how the rest of these samples will *use* a concept - as a
 * constraint on template parameters.
 *
 * Key notes:
 *   - Concepts replace many older techniques: SFINAE, enable_if,
 *     tag dispatch. They give better error messages and are easier to
 *     read.
 *   - The Standard Library defines dozens of concepts in `<concepts>` and
 *     `<iterator>`/`<ranges>`. Prefer those before rolling your own.
 */
template <typename T>
concept Big = sizeof(T) > 4;

static_assert(!Big<char>);
static_assert(!Big<short>);
static_assert(Big<long double>);

int main()
{
}