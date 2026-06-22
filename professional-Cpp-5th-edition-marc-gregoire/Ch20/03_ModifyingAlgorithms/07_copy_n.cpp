/*
 * Chapter 20 - The copy_n Algorithm
 *
 * Demonstrates std::copy_n(), which copies a caller-specified number of elements
 * from a start iterator to a destination. The count is clamped with std::min() and
 * the destination resized accordingly, because copy_n() does no bounds checking -
 * exceeding the source range is undefined behavior.
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

	size_t tally{ 0 };
	print("Enter number of elements you want to copy: ");
	cin >> tally;
	tally = min(tally, size(vec1));
	vec2.resize(tally);
	copy_n(cbegin(vec1), tally, begin(vec2));
	println("{:n}", vec2);
}
