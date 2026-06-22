/*
 * Chapter 1 - switch Statements and [[fallthrough]]
 *
 * A switch picks one of several branches based on a value. Execution starts at the matching
 * case label and continues through subsequent labels until a "break" (or end of switch) is
 * reached - dropping into the next case is called fallthrough. Use [[fallthrough]] (C++17)
 * to mark deliberate fallthrough so the compiler does not warn.
 *
 * Key notes:
 *   - The switch expression must be integral, an enum, an enum class, or a type convertible
 *     to one. Each case label is a compile-time constant.
 *   - The default: label runs when no case matches. Place it last by convention.
 *   - "using enum Mode;" inside the switch scope (shown below) lets you write case Custom
 *     instead of case Mode::Custom. Keep the scope narrow to avoid name pollution.
 *   - C++17 init-statement form: "switch (auto x = compute(); x) { ... }".
 *   - Empty fallthrough between adjacent labels (case A: case B: ...) is not flagged - only
 *     fallthrough after executable code triggers the warning.
 */

int main()
{
	enum class Mode { Default, Custom, Standard };

	int value{ 42 };
	Mode mode{ Mode::Custom };

	switch (mode) {
		using enum Mode;

		case Custom:
			value = 84;
			[[fallthrough]];
		case Standard:
		case Default:
			// Do something with value ...
			break;
	}
}
