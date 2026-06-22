/*
 * Chapter 13 - Output Manipulators
 *
 * Manipulators are objects you "throw down the chute" to change a stream's
 * behavior rather than supply data. This sample tours the common ones:
 * boolalpha/noboolalpha, setw, setfill, noshowpoint, put_money, put_time, and
 * quoted, plus imbue() to format numbers per the current locale. Several
 * println() calls show the equivalent std::format-style output for comparison.
 *
 * Key notes:
 *   - All these manipulators stay in effect until reset, EXCEPT setw, which
 *     applies only to the very next output operation.
 *   - localtime() triggers a security warning on MSVC; it is suppressed here
 *     with a #pragma. Safe alternatives are localtime_s() / localtime_r().
 *   - put_money() requires a long double or a std::basic_string (N5032
 *     [ext.manip]/5). The book passes the string literal "120000"; the newest
 *     MSVC STL rejects that, so this sample wraps it as string{"120000"}.
 */

#include <iostream>
#include <print>
#include <iomanip>
#include <locale>

using namespace std;

int main()
{
	// Boolean values
	bool myBool{ true };
	cout << "This is the default: " << myBool << endl;
	cout << "This should be true: " << boolalpha << myBool << endl;
	cout << "This should be 1: " << noboolalpha << myBool << endl;

	// Simulate println-style "{:6}" with streams
	int i{ 123 };
	println("This should be '   123': {:6}", i);
	cout << "This should be '   123': " << setw(6) << i << endl;

	// Simulate println-style "{:0>6}" with streams
	println("This should be '000123': {:0>6}", i);
	cout << "This should be '000123': " << setfill('0') << setw(6) << i << endl;

	// Fill with *
	cout << "This should be '***123': " << setfill('*') << setw(6) << i << endl;
	// Reset fill character
	cout << setfill(' ');

	// Floating-point values
	double dbl{ 1.452 };
	double dbl2{ 5 };
	cout << "This should be ' 5': " << setw(2) << noshowpoint << dbl2 << endl;
	cout << "This should be @@1.452: " << setw(7) << setfill('@') << dbl << endl;
	// Reset fill character
	cout << setfill(' ');

	// Instructs cout to start formatting numbers according to your location.
	// Chapter 21 explains the details of the imbue() call and the locale object.
	cout.imbue(locale { "" });

	// Format numbers according to your location
	cout << "This is 1234567 formatted according to your location: " << 1234567 << endl;

	// Money amount. What exactly an amount of money means depends on your
	// location. For example, in the USA, a money amount of 120000 means 120000
	// dollar cents, which is 1200.00 dollars.
	cout << "This should be a money amount of 120000, "
		<< "formatted according to your location: "
		<< put_money(string{ "120000" }) << endl;

	// Date and time

#if defined(_MSC_VER)
	// Disable the following Microsoft Visual C++ warning for this example:
	// C4996: 'std::localtime': This function or variable may be unsafe. Consider using localtime_s instead.
	#pragma warning(push)
	#pragma warning(disable : 4996)
#endif

	time_t t_t{ time(nullptr) };     // Get current system time.
	tm t{ *localtime(&t_t) };        // Convert to local time.
	cout << "This should be the current date and time "
		<< "formatted according to your location: "
		<< put_time(&t, "%c") << endl;

#if defined(_MSC_VER)
	#pragma warning(pop) // Restore warning.
#endif

	// Quoted string
	cout << "This should be: \"Quoted string with \\\"embedded quotes\\\".\": "
		<< quoted("Quoted string with \"embedded quotes\".") << endl;
}
