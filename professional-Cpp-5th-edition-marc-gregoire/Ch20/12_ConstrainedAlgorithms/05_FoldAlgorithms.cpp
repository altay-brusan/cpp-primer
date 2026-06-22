/*
 * Chapter 20 - Constrained Fold Algorithms
 *
 * Demonstrates the C++23 ranges fold algorithms. ranges::fold_left_first() folds a
 * range left-to-right using the first element as the initial accumulator, while
 * ranges::fold_right_last() folds right-to-left using the last element. With the
 * non-associative divides<> operator the two directions give different results.
 *
 * Key notes:
 *   - These return a std::optional, so value_or() supplies a fallback for an
 *     empty range.
 */

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>
#include <functional>

using namespace std;

int main()
{
	vector values{ 500.0, 10.0, 2.0 };
	auto foldedLeft{ ranges::fold_left_first(values, divides<>{}) };
	auto foldedRight{ ranges::fold_right_last(values, divides<>{}) };
	println("foldedLeft = {}", foldedLeft.value_or(0.0));
	println("foldedRight = {}", foldedRight.value_or(0.0));
}
