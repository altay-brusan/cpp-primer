/*
 * Chapter 21 - Locale-Aware Character Conversion
 *
 * Demonstrates the locale-parameterized std::toupper() from <locale>, which takes
 * the character to convert and the locale to use. With a French locale, a lowercase
 * accented letter is converted to its uppercase accented form. Note the program has
 * no output statement; the converted value is simply stored in `upper`.
 *
 * Key notes:
 *   - <locale> also provides the matching std::tolower(); both take a character
 *     and a locale argument, unlike the single-argument <cctype> versions.
 */

#include <locale>
#include <cctype>

using namespace std;

int main()
{
	auto upper{ toupper(L'é', locale{ "fr-FR" }) };  // É
}
