/*
 * Chapter 20 - The replace_if Algorithm
 *
 * Demonstrates std::replace_if(), which replaces every element for which a
 * predicate returns true with a new value, in place. Here all odd values in the
 * vector are replaced with 0.
 *
 * Key notes:
 *   - replace() matches a specific value; replace_copy()/replace_copy_if() write
 *     to a separate destination range instead of modifying in place.
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

	replace_if(begin(values), end(values), [](int i){ return i % 2 != 0; }, 0);

	println("{:n}", values);
}
