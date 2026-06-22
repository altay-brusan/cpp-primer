/*
 * Chapter 20 - The copy_if Algorithm
 *
 * Demonstrates std::copy_if(), which copies only the elements satisfying a
 * predicate (here, even numbers) into a destination range. Because copy_if() only
 * overwrites existing elements, the destination is pre-sized; the returned
 * iterator marks one-past-the-last-copied element and is used with erase() to trim
 * the unused tail.
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
	auto endIterator{ copy_if(cbegin(vec1), cend(vec1),
		begin(vec2), [](int i) { return i % 2 == 0; }) };
	vec2.erase(endIterator, end(vec2));
	println("{:n}", vec2);
}
