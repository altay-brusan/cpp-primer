/*
 * Chapter 2 - Targeting a Specific Stream
 *
 * std::println() and std::print() default to stdout, but each accepts a std::ostream
 * (FILE* in some implementations) as an optional first argument. Passing std::cerr sends
 * the formatted message to the standard error stream instead of standard output - useful
 * for diagnostics that should not be mixed with normal program output and that should
 * remain visible even when stdout is redirected to a file or pipe.
 *
 * Key notes:
 *   - println(cerr, "...", args...) writes to standard error; println("...", args...)
 *     writes to standard output.
 *   - cerr is unbuffered, so error messages appear immediately, whereas cout may buffer.
 *   - The same trick works with std::print() when no trailing newline is desired.
 */

#include <print>
#include <iostream>

using namespace std;

int main()
{
	int x{ 42 };
	int y{ 84 };
	println(cerr, "x has value {} and y has value {}.", x, y);
}
