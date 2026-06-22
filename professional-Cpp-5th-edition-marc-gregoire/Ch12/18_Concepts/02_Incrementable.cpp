/*
 * Chapter 12 - Concepts (2/6): requires-expressions, eight ways to apply them
 *
 * A `requires` expression checks that a sequence of expressions is valid
 * for the given type. `requires(T x) { x++; ++x; }` means "T must support
 * both x++ and ++x". The result is a bool.
 *
 * The big block of commented-out templates is the gallery: eight different
 * places you can put a constraint on a function template.
 *
 *   1. `template <typename T> requires Incrementable<T>` - trailing the head.
 *   2. `requires convertible_to<T, bool>`               - standard concept inline.
 *   3. `requires requires(T x){...}`                    - inline ad-hoc constraint.
 *   4. `requires (sizeof(T) == 4)`                      - any boolean expression.
 *   5. `requires Incrementable<T> && Decrementable<T>`  - combine concepts with &&.
 *   6. `requires is_arithmetic_v<T>`                    - any constexpr bool.
 *   7. `void process(...) requires Incrementable<T>`    - trailing the function signature.
 *   8. `template <Incrementable T>`                     - "type-constraint" in the parameter list.
 *
 * The uncommented form at the bottom is the modern, most compact syntax:
 *
 *     void process(const Incrementable auto& t) { ... }
 *
 * It uses the abbreviated-template syntax (sample 16) together with a
 * concept name. Read it as "process takes a const reference to some auto-
 * deduced type that satisfies Incrementable".
 */
#include <concepts>

using namespace std;

template <typename T>
concept Incrementable = requires(T x) { x++; ++x; };

template <typename T>
concept Decrementable = requires(T x) { x--; --x; };

//template <typename T> requires Incrementable<T>
//void process(const T& t)
//{}

//template <typename T> requires convertible_to<T, bool>
//void process(const T& t)
//{}

//template <typename T> requires requires(T x) { x++; ++x; }
//void process(const T& t)
//{}

//template <typename T> requires (sizeof(T) == 4)
//void process(const T& t)
//{}

//template <typename T> requires Incrementable<T>&& Decrementable<T>
//void process(const T& t)
//{}

//template <typename T> requires is_arithmetic_v<T>
//void process(const T& t)
//{}

//template <typename T>
//void process(const T& t) requires Incrementable<T>
//{}

//template <convertible_to<bool> T>
//void process(const T& t)
//{}

//template <Incrementable T>
//void process(const T& t)
//{}

void process(const Incrementable auto& t)
{}

int main()
{
	process(123);
}