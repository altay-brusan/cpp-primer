/*
 * Chapter 1 - The Conditional (Ternary) Operator
 *
 * C++ has exactly one ternary operator: "cond ? a : b". It is an expression (not a statement),
 * so it can appear anywhere a value is needed - inside a function call, on the right side of
 * an assignment, even as the controlling expression of another ternary. Read it as a question:
 * "Is the condition true? If so the value is a, otherwise b."
 *
 * Key notes:
 *   - Both branches must have a common type (or be convertible to one); otherwise the
 *     expression does not compile.
 *   - Parentheses around the condition are optional but help readability when other operators
 *     are nearby.
 *   - Avoid nesting more than one level deep. "a ? b : c ? d : e" is legal but hard to read.
 *   - Unlike if/else, the result is a value you can return or assign directly:
 *         int sign = (x < 0) ? -1 : (x > 0) ? 1 : 0;
 */

#include <print>

using namespace std;

int main()
{
	int i{ 3 };
	println("{}", (i > 2) ? "yes" : "no");
	println("{}", i > 2 ? "yes" : "no");
}
