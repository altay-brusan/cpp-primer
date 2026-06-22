/*
 * Chapter 24 - Decomposing tuples with std::tie
 *
 * Demonstrates std::tie(), the second way to decompose a tuple. tie() builds a
 * tuple of references to existing variables; assigning a tuple to that result
 * writes each element back into the corresponding variable. Unlike structured
 * bindings, tie() can skip elements by using the special std::ignore placeholder
 * in place of a variable, as shown in the second block.
 */

#include <print>
#include <tuple>
#include <string>

using namespace std;

int main()
{
	tuple t1{ 16, "Test"s, true };  // Using CTAD
	// Or:
	//tuple<int, string, bool> t1{ 16, "Test", true };

	{
		int i{ 0 };
		string str;
		bool b{ false };
		println("Before: i = {}, str = \"{}\", b = {}", i, str, b);
		tie(i, str, b) = t1;
		println("After: i = {}, str = \"{}\", b = {}", i, str, b);
	}

	{
		int i{ 0 };
		bool b{ false };
		println("Before: i = {}, b = {}", i, b);
		tie(i, ignore, b) = t1;
		println("After: i = {}, b = {}", i, b);
	}
}