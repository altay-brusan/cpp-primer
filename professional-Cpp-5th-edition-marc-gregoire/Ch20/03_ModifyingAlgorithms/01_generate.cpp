/*
 * Chapter 20 - The generate Modifying Algorithm
 *
 * Demonstrates std::generate(), which overwrites every element in a range with the
 * value returned by a callback. Here a lambda capturing a running value by
 * reference fills a 10-element vector with successive powers of two (2, 4, 8, ...).
 *
 * Key notes:
 *   - generate() works in place on a single range and may use a stateful callback.
 */

#include <print>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> values(10); // Create a vector of 10 elements.
	int value{ 1 };
	generate(begin(values), end(values), [&value]{ value *= 2; return value; });
	println("{:n}", values);
}
