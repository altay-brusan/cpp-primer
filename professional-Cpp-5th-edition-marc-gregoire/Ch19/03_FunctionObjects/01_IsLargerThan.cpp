/*
 * Chapter 19 - Writing Your First Function Object
 *
 * Shows how to turn a class into a function object (functor) by overloading the function
 * call operator. IsLargerThan stores a threshold and its operator()(int, int) returns
 * true only when both arguments exceed it. The functor is passed to the templated
 * findMatches() as the Matcher callback, illustrating that a stateful object can stand in
 * wherever a function pointer is expected - the key advantage over a plain function being
 * that it carries state (the threshold) between calls.
 *
 * Key notes:
 *   - The overloaded call operator is marked const, as Standard Library predicates require.
 */
#include <print>
#include <vector>
#include <span>
#include <functional>
#include <cstddef>

using namespace std;

template<predicate<int, int> Matcher, invocable<size_t, int, int> MatchHandler>
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

void printMatch(size_t position, int value1, int value2)
{
	println("Match found at position {} ({}, {})", position, value1, value2);
}

class IsLargerThan
{
public:
	explicit IsLargerThan(int value) : m_value{ value } {}

	bool operator()(int value1, int value2) const {
		return value1 > m_value && value2 > m_value;
	}

private:
	int m_value;
};

int main()
{
	vector values1{ 2, 500, 6, 9, 10, 101, 1 };
	vector values2{ 4, 4, 2, 9, 0, 300, 1 };

	findMatches(values1, values2, IsLargerThan{ 100 }, printMatch);
}
