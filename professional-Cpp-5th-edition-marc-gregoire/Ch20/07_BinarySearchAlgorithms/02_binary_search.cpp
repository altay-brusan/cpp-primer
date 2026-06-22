/*
 * Chapter 20 - The binary_search Algorithm
 *
 * Demonstrates std::binary_search(), which tests whether a value is present in a
 * sorted range and returns a bool, in logarithmic time by repeatedly halving the
 * range. The vector is sorted first, then the user queries for values.
 *
 * Key notes:
 *   - The range must be sorted; associative containers offer their own find().
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

	// Sort the container
	sort(begin(values), end(values));

	while (true) {
		print("Enter a number to find (0 to stop): ");
		int number;
		cin >> number;
		if (number == 0) {
			break;
		}
		if (binary_search(cbegin(values), cend(values), number)) {
			println("That number is in the vector.");
		} else {
			println("That number is not in the vector.");
		}
	}
}
