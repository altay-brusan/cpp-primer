/*
 * Chapter 21 - Querying a Locale
 *
 * Builds a std::locale from the user's environment (the empty string "") and
 * queries it. The name() method returns a descriptive string for the locale,
 * and string::find() checks whether it contains the US English identifier in
 * either the POSIX form (en_US) or the Windows form (en-US), printing a different
 * greeting depending on the result.
 */

#include <print>
#include <locale>
#include <string>

using namespace std;

int main()
{
	locale loc{ "" };

	if (loc.name().find("en_US") == string::npos &&
		loc.name().find("en-US") == string::npos) {
		println("Welcome non-US English speaker!");
	} else {
		println("Welcome US English speaker!");
	}
}
