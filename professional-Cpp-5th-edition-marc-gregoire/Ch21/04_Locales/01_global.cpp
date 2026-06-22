/*
 * Chapter 21 - The Global Locale
 *
 * Demonstrates std::locale::global(), which replaces the application-wide C++
 * locale. The number 32767 is formatted before and after switching the global
 * locale to US English, so the second output gains thousands separators (32,767).
 *
 * Key notes:
 *   - Standard Library objects that use locales (such as streams) copy the global
 *     locale at construction time; changing the global locale afterward does not
 *     affect already-created objects unless you call imbue() on them.
 */

#include <print>
#include <sstream>
#include <locale>

using namespace std;

void print()
{
	stringstream stream;
	stream << 32767;
	println("{}", stream.str());
}

int main()
{
	print();
	locale::global(locale{ "en-US" }); // "en_US" for POSIX
	print();
}