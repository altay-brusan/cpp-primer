/*
 * Chapter 17 - Repeat View Factory (views::repeat)
 *
 * Minimal example of the C++23 views::repeat range factory, which lazily produces a
 * view yielding the same value repeatedly. views::repeat(42, 5) generates the value
 * 42 five times.
 *
 * Key notes:
 *   - views::repeat is a C++23 feature; requires a C++23 standard library.
 */

#include <print>
#include <ranges>
#include <string_view>

using namespace std;

void printRange(string_view message, auto&& range)
{
	println("{}{:n}", message, range);
}

int main()
{
	// views::repeat
	printRange("Repeating view: ", views::repeat(42, 5));
}
