/*
 * Chapter 20 - Counting with count_if (Capture by Reference)
 *
 * Extends the count_if() example to show lambda capture by reference. In addition
 * to capturing the threshold by value, the predicate captures callCounter by
 * reference and increments it on every invocation, demonstrating how often the
 * algorithm calls the predicate (once per element).
 */

#include <print>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	vector values{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int value{ 3 };
	int callCounter{ 0 };
	auto tally{ count_if(cbegin(values), cend(values),
		[value, &callCounter](int i) { ++callCounter; return i > value; }) };
	println("The lambda expression was called {} times.", callCounter);
	println("Found {} values > {}.", tally, value);
}