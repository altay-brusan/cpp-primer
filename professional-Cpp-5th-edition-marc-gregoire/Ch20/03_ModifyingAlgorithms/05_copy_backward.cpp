/*
 * Chapter 20 - The copy_backward Algorithm
 *
 * Demonstrates std::copy_backward(), which copies a source range into a
 * destination starting from the last element and working backward. Note that the
 * third argument is the destination's end iterator, not its begin. The result is
 * the same element order as copy(); only the copying direction differs, which
 * matters when the ranges overlap.
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
	vector<int> vec1, vec2;

	populateContainer(vec1);

	vec2.resize(size(vec1));

	copy_backward(cbegin(vec1), cend(vec1), end(vec2));

	println("{:n}", vec2);
}
