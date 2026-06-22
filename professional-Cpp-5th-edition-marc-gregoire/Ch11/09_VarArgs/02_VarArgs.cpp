/*
 * Chapter 11 - C-style varargs (2/2): Writing your own variadic function
 *
 * `<cstdarg>` is the legacy C-varargs machinery. The recipe:
 *   - The function signature uses `...` after at least one named parameter.
 *   - `va_list ap;` declares the iterator.
 *   - `va_start(ap, last)` initializes it (last named parameter goes here).
 *   - `va_arg(ap, T)` fetches the next argument as type T - the caller and
 *     callee must agree on the type. No checking!
 *   - `va_end(ap)` releases the iterator.
 *
 * Two demonstrations:
 *   - `debugOut` forwards to `vfprintf` - the classic logging wrapper.
 *   - `printInts` extracts a series of ints based on a count argument.
 *
 * Key notes:
 *   - C varargs are NOT type-safe and they don't play well with non-trivial
 *     C++ types - never pass a `std::string` through `...`, only POD-ish C
 *     types.
 *   - In modern C++ prefer variadic templates and parameter packs
 *     (Chapter 12 / 26). Reach for this API only when wrapping a C function
 *     that already takes `va_list`.
 */
#include <print>
#include <cstdarg>
#include <cstdio>

using namespace std;

bool debug{ false };

void debugOut(const char* str, ...)
{
	if (debug) {
		va_list ap;
		va_start(ap, str);
		vfprintf(stderr, str, ap);
		va_end(ap);
	}
}

void printInts(unsigned num, ...)
{
	va_list ap;
	va_start(ap, num);
	for (unsigned i{ 0 }; i < num; ++i) {
		int temp{ va_arg(ap, int) };       // caller MUST have passed int here
		print("{} ", temp);
	}
	va_end(ap);
	println("");
}

int main()
{
	debug = true;
	debugOut("int %d\n", 5);
	debugOut("String %s and int %d\n", "hello", 5);
	debugOut("Many ints: %d, %d, %d, %d, %d\n", 1, 2, 3, 4, 5);

	printInts(5, 5, 4, 3, 2, 1);
}
