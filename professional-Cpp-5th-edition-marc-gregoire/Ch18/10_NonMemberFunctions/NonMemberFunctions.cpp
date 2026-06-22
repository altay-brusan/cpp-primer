/*
 * Chapter 18 - Non-Member size(), empty(), and ssize()
 *
 * Demonstrates the global helpers that work across containers: std::size() and
 * std::empty(), plus C++20's std::ssize(), which returns the size as a signed
 * type (long long) rather than the unsigned size_t returned by size().
 */

#include <print>
#include <vector>

using namespace std;

int main()
{
	vector vec{ 1, 2, 3 };
	println("{}", size(vec));
	println("{}", empty(vec));

	auto s1{ size(vec) };   // Type is size_t (unsigned)
	auto s2{ ssize(vec) };  // Type is long long (signed)
}
