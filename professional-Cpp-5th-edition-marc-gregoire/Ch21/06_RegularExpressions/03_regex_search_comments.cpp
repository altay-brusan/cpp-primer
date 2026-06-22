/*
 * Chapter 21 - regex_search: Finding a Substring
 *
 * Uses std::regex_search(), which (unlike regex_match) succeeds when the pattern
 * matches some substring of the input rather than the whole input. The pattern
 * looks for a C++ line comment marker, optional whitespace, then captures the rest
 * of the line up to the end-of-line anchor into a capture group. On success, the
 * captured comment text is read from m[1].str() and printed.
 *
 * Key notes:
 *   - match_results also offers prefix() and suffix() to get the text before and
 *     after the matched substring.
 */

#include <print>
#include <regex>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	regex r{ "//\\s*(.+)$" };
	while (true) {
		print("Enter a string with optional code comments (q=quit):\n> ");
		string str;
		if (!getline(cin, str) || str == "q") {
			break;
		}

		if (smatch m; regex_search(str, m, r)) {
			println("  Found comment '{}'", m[1].str());
		} else {
			println("  No comment found!");
		}
	}
}
