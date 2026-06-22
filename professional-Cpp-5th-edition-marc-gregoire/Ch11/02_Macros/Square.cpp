/*
 * Chapter 11 - Preprocessor Macros (and why to avoid them)
 *
 * `#define SQUARE(x) ((x) * (x))` is the textbook example of why macros are
 * dangerous: they look like functions but they're just text substitution.
 * Without the parentheses around `x` and around the whole body, an
 * expression like `SQUARE(2 + 3)` would expand to `2 + 3 * 2 + 3` = 11,
 * not 25.
 *
 * Even when written carefully, macros have other problems:
 *   - No type checking. `SQUARE("hi")` gets you a confusing compile error
 *     far from the call site.
 *   - Argument is evaluated twice. `SQUARE(++i)` increments i twice.
 *   - No scope, no namespace - macros leak into every file that #includes
 *     yours, with all the name collisions that implies.
 *
 * Modern alternative:
 *   inline constexpr auto square(auto x) { return x * x; }
 *
 * Macros still earn their keep for things the language can't express -
 * include guards (replaced by `#pragma once` or modules), conditional
 * compilation (`#ifdef`), and code generation glue. For "I want a small
 * function", reach for a function or a template.
 */
#include <print>

using namespace std;

#define SQUARE(x) ((x) * (x)) // No semicolon after the macro definition!
//#define SQUARE(x) (x * x)   // <-- the trap version: SQUARE(2+3) becomes 2+3*2+3

int main()
{
	println("{}", SQUARE(5));      // 25
	println("{}", SQUARE(2 + 3));  // 25 (because of the inner parentheses)
}
