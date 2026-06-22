/*
 * Chapter 1 - [[nodiscard]]
 *
 * [[nodiscard]] on a value-returning function makes the compiler warn when a caller throws
 * the result away. It is the right hammer for error codes, status enums, and anything else
 * that is unsafe to ignore.
 *
 * Key notes:
 *   - Can be applied to functions, classes/structs (every function returning that type then
 *     inherits the diagnostic), and enumeration types.
 *   - Since C++20 you can include a reason string: [[nodiscard("Closes the handle")]].
 *   - To intentionally discard the result, cast to void: "(void)func();" - this silences the
 *     warning and documents the intent.
 *   - Standardized in C++17.
 */

[[nodiscard]] int func()
{
	return 42;
}

int main()
{
	func();
}
