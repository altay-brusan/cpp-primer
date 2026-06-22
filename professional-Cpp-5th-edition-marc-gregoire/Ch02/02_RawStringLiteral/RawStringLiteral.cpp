/*
 * Chapter 2 - Raw String Literals
 *
 * A raw string literal preserves every character between its delimiters verbatim. It is
 * written R"(...)" - the characters inside the parentheses appear in the resulting string
 * exactly as typed, so backslashes do not start escape sequences and double quotes do not
 * need to be escaped. Raw literals may also span physical source lines, with each newline
 * in the source becoming a newline in the value. When the contents themselves need to
 * include the sequence )", switch to the extended form R"delim(...)delim" and pick a
 * short delimiter (up to 16 characters) that does not occur in the payload.
 *
 * Key notes:
 *   - \t, \n, \", etc. are NOT processed inside R"(...)" - they stay as literal characters.
 *   - The basic form ends at the FIRST occurrence of )", so payloads containing )" need
 *     the extended form, e.g. R"-(Embedded )" characters)-".
 *   - Great fit for Windows paths (R"(c:\temp\file.txt)"), regex patterns, SQL, and JSON
 *     fragments - all places where escaping would otherwise pile up.
 *   - Whitespace at the start of continued lines becomes part of the string; mind your
 *     indentation when embedding multi-line raw literals.
 *   - The leading R prefix can be combined with character-type prefixes (LR"(...)",
 *     u8R"(...)", uR"(...)", UR"(...)") for wide/UTF encodings.
 * 	 - R stands for Raw, and the delimiters can be customized to avoid conflicts with the content.
 *   - R"delimiter( ... )delimiter"
 *
 * Example:
 *     const char* str { R"-(Embedded )" characters)-" };  // delimiter is -
 */

#include <print>

using namespace std;

int main()
{
	//println("Hello "World"!");    // Error!
	println("Hello \"World\"!");
	println(R"(Hello "World"!)");

	println("Line 1\nLine 2");
	println(R"(Line 1
Line 2)");

	println(R"(Is the following a tab character? \t)");

	//println(R"(Embedded )" characters)");    // Error!
	println(R"-(Embedded )" characters)-");
}
