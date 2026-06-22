/*
 * Chapter 21 - Locale-Aware Character Classification
 *
 * Demonstrates the locale-parameterized std::isupper() from <locale>, which takes
 * both the character to classify and the locale to classify it in. Using a French
 * locale, the accented capital letter is reported as uppercase while its lowercase
 * form is not, showing classification that respects accented letters.
 *
 * Key notes:
 *   - <locale> provides a whole family of such functions: isspace, isalpha,
 *     isdigit, ispunct, and so on, each taking a character and a locale.
 */

#include <print>
#include <locale>
#include <cctype>

using namespace std;

int main()
{
	println("É {}", isupper(L'É', locale{ "fr-FR" }));
	println("é {}", isupper(L'é', locale{ "fr-FR" }));
}
