/*
 * Chapter 2 - Escaped (Debug) Output: the ? Type (C++23)
 *
 * The ? format type prints a string or character in its escaped, "debug-style" form.
 * Control characters such as '\t' and '\n' come out as the literal escape sequences \t
 * and \n instead of being executed, embedded quote characters are escaped, and the value
 * is wrapped in quotes - single quotes for char, double quotes for strings. This is the
 * formatter equivalent of how a debugger displays a string and is the easiest way to
 * make non-printable content visible in normal output.
 *
 * Key notes:
 *   - {:?} on a std::string or const char* wraps it in "..." with control characters
 *     escaped: "Hello\tWorld!\n" prints as "Hello\tWorld!\n".
 *   - {:?} on a char wraps it in '...': '\'' prints as '\''.
 *   - Useful for logging input that may contain tabs, newlines, or quotes, where the
 *     literal characters would otherwise corrupt the output.
 *   - The ? specifier requires C++23 formatting support.
 */

#include <print>

using namespace std;

int main()
{
	// Escaped output
	println("|{:?}|", "Hello\tWorld!\n");  // |Hello\tWorld!\n|
	println("|{:?}|", "\"");               // |"\""|
	println("|{:?}|", '\'');               // |'\''|
	println("|{:?}|", '"');                // |'"'|
}
