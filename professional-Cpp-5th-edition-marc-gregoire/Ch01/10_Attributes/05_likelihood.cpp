/*
 * Chapter 1 - [[likely]] and [[unlikely]]
 *
 * The C++20 likelihood attributes hint to the optimizer which branch of an if/else, or which
 * case label of a switch, is the common path. The compiler can then favor that path for
 * inlining and instruction layout.
 *
 * Key notes:
 *   - Modern CPUs and compilers already have powerful branch prediction. Reach for these
 *     attributes only after profiling shows a hot misprediction.
 *   - Syntax: place the attribute on the controlled statement, not on the condition:
 *         if (x) [[likely]] { ... } else [[unlikely]] { ... }
 *         switch (x) { [[likely]] case 1: ... break; ... }
 *   - Misusing them (hinting the wrong branch) can hurt performance instead of helping.
 *   - Has no effect on program semantics; purely an optimization hint.
 */

int main()
{
	int value{ 4 };
	if (value > 11) [[unlikely]] { /* Do something ... */ }
	else { /* Do something else... */ }

	switch (value)
	{
	[[likely]] case 1:
		// Do something ...
		break;
	case 2:
		// Do something...
		break;
	[[unlikely]] case 12:
		// Do something...
		break;
	}
}