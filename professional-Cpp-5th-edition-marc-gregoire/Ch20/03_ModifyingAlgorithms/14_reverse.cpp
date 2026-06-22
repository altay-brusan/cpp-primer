/*
 * Chapter 20 - The reverse Algorithm
 *
 * Demonstrates std::reverse(), which reverses the order of the elements in a range
 * in place by swapping the first with the last, the second with the second-to-last,
 * and so on.
 *
 * Key notes:
 *   - reverse_copy() writes the reversed sequence to a separate destination range.
 */

#include <print>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// Function template to populate a container of ints.
// A constraint enforces that the container supports push_back(int).
template<typename Container>
	requires requires(Container& c, int i) { c.push_back(i); }
void populateContainer(Container& cont)
{
	while (true) {
		print("Enter a number (0 to stop): ");
		int value;
		cin >> value;
		if (value == 0) {
			break;
		}
		cont.push_back(value);
	}
}

int main()
{
	vector<int> values;
	populateContainer(values);

	reverse(begin(values), end(values));

	println("{:n}", values);
}
