/*
 * Chapter 24 - std::pair
 *
 * Demonstrates std::pair from <utility>, which stores exactly two values, each
 * with its own type fixed at compile time. The elements are accessed through the
 * .first and .second members. The sample also shows class template argument
 * deduction (CTAD), which lets the compiler deduce the element types from the
 * initializers, and that since C++23 std::println has built-in formatting
 * support for a pair as a whole. A pair is the two-element special case of the
 * more general std::tuple covered in the rest of this folder.
 */

#include <print>
#include <utility>
#include <string>

using namespace std;

int main()
{
	pair<int, string> p1{ 16, "Hello World" };
	pair p2{ true, 0.123f };
	println("p1 = ({}, {})", p1.first, p1.second);
	println("p2 = ({}, {})", p2.first, p2.second);

	// Starting with C++23, println() has full support for pair.
	println("p1 = {}", p1);
	println("p2 = {}", p2);
}
