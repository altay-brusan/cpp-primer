/*
 * Chapter 24 - Comparing tuples
 *
 * Demonstrates that tuples support all comparison operators, performing an
 * element-by-element lexicographical comparison (provided each element type is
 * itself comparable). The two tuples here share the same first element, so the
 * result is decided by comparing the second (string) elements.
 */

#include <print>
#include <tuple>

using namespace std;

int main()
{
	tuple t1{ 123, "def"s };  // Using CTAD.
	tuple t2{ 123, "abc"s };
	// Or:
	//tuple<int, string> t1{ 123, "def" };
	//tuple<int, string> t2{ 123, "abc" };

	if (t1 < t2) {
		println("t1 < t2");
	} else {
		println("t1 >= t2");
	}
}
