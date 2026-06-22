/*
 * Chapter 21 - Imbuing Streams with Locales
 *
 * Shows how to attach a std::locale to a stream with imbue() so that subsequent
 * output is formatted according to that locale's rules. The same number 32767 is
 * printed under the user's locale (empty string ""), the neutral classic "C"
 * locale (no punctuation), and the explicit "en-US" locale (32,767). It then
 * contrasts std::println and std::format, where the L format specifier requests
 * locale-aware formatting, with a locale passed directly to format().
 *
 * Key notes:
 *   - The empty string "" selects the user's environment locale; "C" is the
 *     neutral classic locale recommended for machine-readable output.
 */

#include <print>
#include <sstream>
#include <locale>
#include <iostream>
#include <format>

using namespace std;

int main()
{
	cout.imbue(locale{ "" });
	cout << "User's locale: " << 32767 << endl;

	cout.imbue(locale{ "C" });
	cout << "C locale: " << 32767 << endl;

	cout.imbue(locale{ "en-US" }); // "en_US" for POSIX
	cout << "en-US locale: " << 32767 << endl;
	
	locale::global(locale{ "en-US" }); // "en_US" for POSIX
	println("println(): {}", 32767);
	println("println() using global locale: {:L}", 32767);
	cout << format(locale{ "en-US" }, "format() with en-US locale: {:L}", 32767);
}