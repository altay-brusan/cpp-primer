/*
 * Chapter 21 - regex_replace with the format_no_copy Flag
 *
 * Same HTML substitution as the previous example, but passes
 * regex_constants::format_no_copy. This flag tells regex_replace() to emit only the
 * replacement text for matched portions and to drop everything that did not match,
 * so the surrounding body tags are not copied into the result.
 *
 * Key notes:
 *   - Other useful flags are format_first_only (replace only the first match) and
 *     the default format_default (replace all and copy non-matching text).
 */

#include <print>
#include <regex>
#include <string>

using namespace std;

int main()
{
	const string str{ "<body><h1>Header</h1><p>Some text</p></body>" };
	regex r{ "<h1>(.*)</h1><p>(.*)</p>" };

	const string replacement{ "H1=$1 and P=$2" };
	string result{ regex_replace(str, r, replacement, regex_constants::format_no_copy) };
	
	println("Original string: '{}'", str);
	println("New string     : '{}'", result);
}
