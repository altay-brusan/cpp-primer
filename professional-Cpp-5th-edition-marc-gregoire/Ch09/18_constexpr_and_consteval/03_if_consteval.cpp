/*
 * Chapter 9 - if consteval (C++23)
 *
 * Inside a `constexpr` function, `if consteval { ... } else { ... }` picks one
 * branch when the surrounding evaluation is happening at compile time and the
 * other when it is happening at runtime. That lets a single function call out
 * to `consteval`-only helpers in the compile-time branch while still offering
 * a sensible runtime path.
 *
 * Key notes:
 *   - The compile-time branch may call `consteval` functions like `f(i)` above -
 *     legal because we are guaranteed to be in a constant evaluation there.
 *   - The runtime branch must NOT call `consteval` functions; doing so is an
 *     error.
 *   - This replaces the older `std::is_constant_evaluated()` pattern. The new
 *     form is a statement, not a runtime function call.
 *   - Requires a C++23-aware compiler.
 */
// An immediate function.
consteval int f(int i)
{
	return i;
}

// A constexpr function.
constexpr int g(int i)
{
	if consteval { return f(i); }
	else { return 42; }
}


int main()
{
	g(21);
}
