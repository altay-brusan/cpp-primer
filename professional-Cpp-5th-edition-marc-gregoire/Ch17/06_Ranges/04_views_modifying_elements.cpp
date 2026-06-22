/*
 * Chapter 17 - Modifying Underlying Elements Through a View
 *
 * Demonstrates that a view is non-owning but can still be used to write back into
 * the underlying range when the view is not read-only. A pipeline of filter (even
 * values), drop(2), and reverse produces a mutable view; a range-based for loop with
 * a non-const reference multiplies each viewed element by 10. Printing the original
 * vector afterward confirms only the elements reachable through the view were
 * changed.
 *
 * Key notes:
 *   - views::transform yields a read-only view, so it could not be used as the last
 *     step if you intend to write back through it.
 */

#include <print>
#include <ranges>
#include <vector>
#include <string_view>

using namespace std;

void printRange(string_view message, auto&& range)
{
	println("{}{:n}", message, range);
}

int main()
{
	vector values{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	printRange("Original sequence: ", values);

	// Filter out all odd values, leaving only the even values.
	auto result1{ values
		| views::filter([](const auto& value) { return value % 2 == 0; }) };
	printRange("Only even values: ", result1);

	// Drop the first 2 elements.
	auto result2{ result1 | views::drop(2) };
	printRange("First two dropped: ", result2);

	// Reverse the view.
	auto result3{ result2 | views::reverse };
	printRange("Sequence reversed: ", result3);

	// Modify the elements using a range-based for loop.
	for (auto& value : result3) { value *= 10; }
	printRange("After modifying elements through a view, vector contains:\n", values);
}
