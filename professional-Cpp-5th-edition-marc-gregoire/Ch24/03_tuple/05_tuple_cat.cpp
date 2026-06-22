/*
 * Chapter 24 - Concatenating tuples with std::tuple_cat
 *
 * Demonstrates std::tuple_cat(), which joins two (or more) tuples into a single
 * tuple whose element types are the concatenation of the inputs' element types.
 * Here a tuple<int, string, bool> and a tuple<double, string> combine into a
 * tuple<int, string, bool, double, string>, built with CTAD and printed as a
 * whole using C++23 println support.
 */

#include <print>
#include <tuple>
#include <string>

using namespace std;

int main()
{
	tuple t1{ 16, "Test"s, true };  // Using CTAD
	tuple t2{ 3.14, "string 2"s };
	// Or:
	//tuple<int, string, bool> t1{ 16, "Test", true };
	//tuple<double, string> t2{ 3.14, "string 2" };

	auto t3{ tuple_cat(t1, t2) };

	println("t3 = {}", t3);
}
