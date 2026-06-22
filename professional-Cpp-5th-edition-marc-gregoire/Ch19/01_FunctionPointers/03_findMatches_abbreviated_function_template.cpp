/*
 * Chapter 19 - findMatches() as an Abbreviated Function Template
 *
 * Identical behavior to the explicit function-template version, but written using the
 * C++20 abbreviated function template syntax: the callback parameters are declared with
 * constrained auto - predicate<int, int> auto matcher and
 * invocable<size_t, int, int> auto handler - turning findMatches() into a template
 * without an explicit template parameter list. This is the recommended, most concise way
 * to accept arbitrary callbacks.
 */
#include <print>
#include <vector>
#include <span>

using namespace std;

void findMatches(span<const int> values1, span<const int> values2,
	predicate<int, int> auto matcher, invocable<size_t, int, int> auto handler)
{
	if (values1.size() != values2.size()) { return; } // Must be same size.

	for (size_t i{ 0 }; i < values1.size(); ++i) {
		if (matcher(values1[i], values2[i])) {
			handler(i, values1[i], values2[i]);
		}
	}
}

bool intEqual(int value1, int value2)
{
	return value1 == value2;
}

bool bothOdd(int value1, int value2)
{
	return value1 % 2 == 1 && value2 % 2 == 1;
}

void printMatch(size_t position, int value1, int value2)
{
	println("Match found at position {} ({}, {})", position, value1, value2);
}

int main()
{
	vector values1{ 2, 5, 6, 9, 10, 1, 1 };
	vector values2{ 4, 4, 2, 9, 0, 3, 1 };
	println("Calling findMatches() using intEqual():");
	findMatches(values1, values2, intEqual, printMatch);

	println("Calling findMatches() using bothOdd():");
	findMatches(values1, values2, bothOdd, printMatch);
}
