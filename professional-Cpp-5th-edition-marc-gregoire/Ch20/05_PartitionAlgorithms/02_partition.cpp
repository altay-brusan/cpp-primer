/*
 * Chapter 20 - The partition Algorithm
 *
 * Demonstrates std::partition(), which reorders a range in place so that all
 * elements satisfying a predicate come before all those that do not. Here the
 * vector is partitioned into even numbers followed by odd numbers. The relative
 * order within each group is not preserved (use stable_partition() for that).
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
	
	partition(begin(values), end(values), [](int i){ return i % 2 == 0; });

	println("Partitioned result: {:n}", values);
}
