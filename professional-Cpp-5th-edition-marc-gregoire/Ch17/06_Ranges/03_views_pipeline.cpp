/*
 * Chapter 17 - Composing Views into a Pipeline
 *
 * Shows that the separate filter/transform/drop/reverse steps from the previous
 * example can be chained into one expression with the pipe operator, building a
 * single lazy pipeline from the vector to the final view. No intermediate views are
 * named, and nothing is computed until printRange() iterates the result. The output
 * matches the step-by-step version.
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

	auto result{ values
		| views::filter([](const auto& value) { return value % 2 == 0; })
		| views::transform([](const auto& value) { return value * 2.0; })
		| views::drop(2)
		| views::reverse };
	printRange("Final sequence: ", result);
}
