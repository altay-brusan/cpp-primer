/*
 * Chapter 19 - findMatches() with std::function Parameters
 *
 * The findMatches() callback example with the Matcher and MatchHandler type aliases
 * redefined as std::function types (function<bool(int, int)> and
 * function<void(size_t, int, int)>) instead of raw function pointers. Because
 * std::function can wrap any matching callable, the same function pointers (intEqual,
 * bothOdd, printMatch) pass straight through. This is the std::function alternative to the
 * template-based versions in folder 01.
 */
#include <print>
#include <vector>
#include <functional>
#include <span>

using namespace std;

// A type alias for a function accepting two integer values,
// returning true if both values are matching, false otherwise.
using Matcher = function<bool(int, int)>;

// A type alias for a function to handle a match. The first
// parameter is the position of the match,
// the second and third are the values that matched.
using MatchHandler = function<void(size_t, int, int)>;

void findMatches(span<const int> values1, span<const int> values2,
	Matcher matcher, MatchHandler handler)
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
