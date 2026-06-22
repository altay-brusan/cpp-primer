/*
 * Chapter 1 - [[maybe_unused]]
 *
 * [[maybe_unused]] silences "unreferenced parameter" or "unused variable" warnings on items
 * that are intentionally unused (perhaps under some build configurations). Applied to param2
 * here, so only param1 still earns a warning.
 *
 * Key notes:
 *   - Can decorate variables, function parameters, functions, classes, structs, unions,
 *     enums, enumerators, typedefs, and type aliases.
 *   - Better than (void)param; or commenting the parameter name out - it keeps the name
 *     visible in the signature for documentation.
 *   - Standardized in C++17.
 */

int func(int param1, [[maybe_unused]] int param2)
{
	return 42;
}

int main()
{
	int result{ func(1, 2) };
}