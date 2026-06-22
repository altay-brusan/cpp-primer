/*
 * Chapter 11 - Anonymous Namespaces (the hidden function side)
 *
 * Anything declared inside `namespace { ... }` has internal linkage - the
 * modern equivalent of file-scope `static`. The function is reachable from
 * THIS translation unit only.
 *
 * Why use it:
 *   - Helper functions and types that should not leak to other TUs.
 *   - Avoid ODR violations - two different TUs can each define their own
 *     `f()` inside an anonymous namespace without colliding.
 *   - Preferred over `static` for non-extern declarations in modern C++.
 *
 * In this sample the unnamed namespace is precisely what BREAKS the link
 * step in FirstFile.cpp: FirstFile's reference to `f()` looks for an
 * external symbol, but this `f()` only exists inside this TU.
 */
#include <print>

namespace
{
	void f();

	void f()
	{
		std::println("f");
	}
}
