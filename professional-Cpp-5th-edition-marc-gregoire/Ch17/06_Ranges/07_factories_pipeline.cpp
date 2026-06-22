/*
 * Chapter 17 - Range Factory in a Single Pipeline
 *
 * The pipeline form of the previous factory example: views::iota(10) feeds directly
 * into filter, transform, and take(10) as one chained expression, with no named
 * intermediate views. Demonstrates again that an infinite factory source combined
 * with lazy adapters only materializes the requested elements.
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
	auto result{ views::iota(10)
		| views::filter([](const auto& value) {return value % 2 == 0; })
		| views::transform([](const auto& value) {return value * 2.0; })
		| views::take(10) };
	printRange("Result: ", result);
}
