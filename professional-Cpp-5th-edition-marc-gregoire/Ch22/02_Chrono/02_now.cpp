/*
 * Chapter 22 - Getting the Current Time from a Clock
 *
 * Shows system_clock::now(), which returns a time_point for the current wall-clock
 * time (UTC). The result is formatted with std::format/println, including the {:L}
 * locale-aware modifier and a chrono format spec (%c) to print it using the
 * current locale's date and time representation.
 *
 * Key notes:
 *   - system_clock measures real calendar time and can be mapped to and from
 *     time_t; it is not guaranteed to be monotonic.
 */

#include <print>
#include <chrono>
#include <locale>

using namespace std;
using namespace std::chrono;

int main()
{
	// Set the global locale to the user's local (see Chapter 21).
	locale::global(locale{ "" });

	// Print the current UTC time.
	println("UTC: {:L}", system_clock::now());
	println("UTC: {:L%c}", system_clock::now());
}
