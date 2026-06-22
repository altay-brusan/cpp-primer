/*
 * Chapter 21 - regex_replace: Basic Substitution
 *
 * Uses std::regex_replace() to transform an HTML string. The pattern captures the
 * header and paragraph contents in two capture groups, and the replacement string
 * references them with the dollar-number escapes (the first capture group as $1 and
 * the second as $2) to build a new string. With the default flags, parts of the
 * input that do not match the pattern are copied through to the result unchanged.
 *
 * Key notes:
 *   - regex_replace() returns the resulting string; the original is not modified.
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
	string result{ regex_replace(str, r, replacement) };
	
	println("Original string: '{}'", str);
	println("New string     : '{}'", result);
}
