/*
 * Chapter 1 - Three-Way Comparisons (the spaceship operator)
 *
 * The C++20 operator "<=>" returns an ordering category instead of a bool, so one expression
 * answers "less, equal, or greater?" at once. That is a real win for types where comparing is
 * expensive: one call gives the full ordering, replacing two separate comparison operators.
 *
 * Key notes:
 *   - The result type lives in <compare> and depends on the operands:
 *       std::strong_ordering    integral types -> less, equal, greater
 *       std::weak_ordering      user types that are equivalent but not identical
 *       std::partial_ordering   floating-point -> less, greater, equivalent, unordered
 *     "unordered" appears when one operand is NaN.
 *   - These ordering types behave like enums but cannot be used as switch labels or in a
 *     "using enum" declaration.
 *   - Default the operator on your class to get all six relational operators for free:
 *         auto operator<=>(const Foo&) const = default;
 *   - For primitives, "<=>" is rarely shorter than ==/</>; the gain is with heavy objects and
 *     with =default on classes.
 */

#include <print>
#include <compare>

using namespace std;

int main()
{
	int i{ 11 };
	strong_ordering result{ i <=> 0 };
	if (result == strong_ordering::less) { println("less"); }
	if (result == strong_ordering::greater) { println("greater"); }
	if (result == strong_ordering::equal) { println("equal"); }
}