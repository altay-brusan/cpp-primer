/*
 * Chapter 2 - Format Specifier Errors at Run Time
 *
 * A malformed format string - missing precision, invalid type letter, out-of-range index,
 * and so on - that survives to run time causes the formatting library to throw a
 * std::format_error. This only happens through the v* family (vformat, vprint_unicode,
 * vprint_nonunicode), because compile-time format strings are already rejected by the
 * compiler. The thrown exception carries a descriptive message available via what().
 *
 * Key notes:
 *   - Catch std::format_error by const reference: `catch (const std::format_error& e)`.
 *   - The example references {5} with only one argument, so it throws "Argument not found."
 *   - With compile-time formatting (format()/println() on literal strings), the same
 *     mistake would be caught at build time instead of throwing.
 *   - Always wrap calls to vformat / vprint_* in try/catch when the format string is
 *     external (e.g., user-supplied or localized resource).
 *   - std::format_error inherits from std::runtime_error, so it can also be caught by a
 *     handler for std::runtime_error or std::exception.
 */

#include <print>
#include <format>
#include <iostream>

using namespace std;

int main()
{
	try {
		int number{ 42 };
		vprint_unicode(cout, "An integer: {5}", make_format_args(number));
	} catch (const format_error& caught_exception) {
		println("{}", caught_exception.what()); // "Argument not found."
	}
}