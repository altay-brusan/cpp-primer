/*
 * Chapter 17 - Range Factories (iota)
 *
 * Introduces range factories, which construct views that generate values on demand.
 * views::iota(10) produces an infinite lazy sequence 10, 11, 12, ... which is then
 * filtered to even values, transformed to doubles, and limited with views::take(10).
 * Because the whole pipeline is lazily evaluated, working with an infinite source is
 * fine: only the ten elements actually requested by printRange() are ever computed.
 *
 * Key notes:
 *   - You must not iterate the infinite intermediate views (values, result1,
 *     result2) directly; only the take(10)-bounded result is safe to print.
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
	// Create an infinite sequence of the numbers 10, 11, 12, ...
	auto values{ views::iota(10) };
	// Filter out all odd values, leaving only the even values.
	auto result1{ values | views::filter([](const auto& value) {return value % 2 == 0; }) };
	// Transform all values to their double value.
	auto result2{ result1 | views::transform([](const auto& value) {return value * 2.0; }) };
	// Take only the first ten elements.
	auto result3{ result2 | views::take(10) };
	printRange("Result: ", result3);
}
