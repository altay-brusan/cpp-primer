/*
 * Chapter 20 - Constrained Algorithms: ranges::for_each with a View
 *
 * Demonstrates composing a constrained algorithm with a range view.
 * std::ranges::for_each() is applied to a filtered view (views::filter selecting
 * even numbers), and the callback multiplies each selected element by 10 in place,
 * leaving the odd elements untouched.
 */

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>

using namespace std;

int main()
{
	vector values{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	println("Before: {:n}", values);

	ranges::for_each(values | views::filter([](int value) { return value % 2 == 0; }),
		[](int& value) { value *= 10; });
	println("After:  {:n}", values);
}
