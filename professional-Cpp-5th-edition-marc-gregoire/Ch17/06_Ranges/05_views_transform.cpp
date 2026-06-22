/*
 * Chapter 17 - Mapping Elements to a Different Type
 *
 * Shows that views::transform can map a range to elements of an entirely different
 * type. The pipeline filters even values, keeps the first three with views::take(3),
 * and transforms each remaining int into a formatted string via std::format. The
 * result is a lazy view of strings produced from a range of ints.
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
		| views::filter([](const auto& value) {return value % 2 == 0; })
		| views::take(3)
		| views::transform([](const auto& v) { return format("{}", v); }) };
	printRange("Result: ", result);
}
