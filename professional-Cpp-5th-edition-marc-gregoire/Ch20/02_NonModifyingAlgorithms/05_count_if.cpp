/*
 * Chapter 20 - Counting with count_if (Capture by Value)
 *
 * Uses std::count_if() to count how many elements satisfy a predicate. The lambda
 * captures the threshold variable "value" by value, then counts how many elements
 * are greater than it.
 */

#include <print>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	vector values{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int value{ 3 };
	auto tally{ count_if(cbegin(values), cend(values),
		[value](int i) { return i > value; }) };
	println("Found {} values > {}.", tally, value);
}