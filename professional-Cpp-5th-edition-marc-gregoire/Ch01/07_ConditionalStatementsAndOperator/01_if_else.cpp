/*
 * Chapter 1 - if/else Statements
 *
 * The most common conditional. The expression in parentheses must be a bool or be convertible
 * to one - 0 counts as false, any non-zero value as true. A cascading if/else-if/else chain
 * runs the first branch whose condition is true; the trailing "else" handles "none matched".
 *
 * Key notes:
 *   - Always brace the body, even for one-liner branches. It prevents the classic dangling-else
 *     and "added a line, forgot the braces" bugs.
 *   - C++17 init-statement form: "if (auto value = compute(); value > 0) { ... }". The
 *     variable is in scope for the whole if/else chain and dies at the end of it.
 *   - Watch for "=" vs "==": "if (x = 3)" assigns 3 to x and is always true. Enable warnings.
 *   - "if constexpr (cond)" picks a branch at compile time (template-heavy code).
 *
 * Example:
 *     if (auto opt = find(); opt) { use(*opt); } else { handleMissing(); }
 */

int main()
{
	int i{ 3 };

	if (i > 4) {
		// Do something.
	} else if (i > 2) {
		// Do something else.
	} else {
		// Do something else.
	}
}
