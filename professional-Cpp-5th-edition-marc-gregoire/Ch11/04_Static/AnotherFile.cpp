/*
 * Chapter 11 - File-scope static (function side)
 *
 * As-shipped: `void f();` has external linkage and the definition is
 * therefore visible to FirstFile.cpp at link time.
 *
 * Uncomment the `static void f();` line to give it internal linkage. The
 * compile step will still succeed, but the link step will fail because
 * FirstFile.cpp's reference goes unresolved.
 *
 * Modern style favors anonymous namespaces (sample 03) over file-scope
 * `static` because:
 *   - Anonymous namespaces also hide types, not just functions/variables.
 *   - `static` is also used for two unrelated things (class members,
 *     storage duration in functions), so reading it requires more context.
 */
#include <print>

void f();
//static void f();   // <-- uncomment to make the link step fail

void f()
{
	std::println("f");
}
