/*
 * Chapter 17 - Input Streams as Views (istream_view)
 *
 * Uses the ranges::istream_view<int> range factory to treat standard input as a lazy
 * view of integers read via operator>>. A range-based for loop drives a pipeline that
 * keeps reading while values are below 5 (views::take_while) and doubles each one
 * (views::transform), printing results until a number >= 5 stops the loop. Because
 * the view is lazy, each integer is read from cin only as the loop advances.
 *
 * Key notes:
 *   - Requires interactive input from the console.
 */

#include <print>
#include <ranges>
#include <string_view>
#include <iostream>

using namespace std;

int main()
{
	println("Type integers, an integer >= 5 stops the program.");
	for (auto value : ranges::istream_view<int>{ cin }
		| views::take_while([](const auto& v) { return v < 5; })
		| views::transform([](const auto& v) { return v * 2; })) {
		println("> {}", value);
	}
	println("Terminating...");
}
