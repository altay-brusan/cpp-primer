/*
 * Chapter 20 - transform (Binary, Two Ranges)
 *
 * Demonstrates the binary overload of std::transform(), which calls a two-argument
 * callback on pairs of elements taken from two input ranges. Here the lambda adds
 * corresponding elements of vec1 and vec2, storing each sum back into vec1.
 *
 * Key notes:
 *   - The second range must be at least as long as the first.
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
	println("Vector1:"); populateContainer(vec1);
	println("Vector2:"); populateContainer(vec2);

	if (vec2.size() < vec1.size())
	{
		println("Vector2 should be at least the same size as vector1.");
		return 1;
	}

	println("Vector1: {:n}", vec1);
	println("Vector2: {:n}", vec2);

	transform(begin(vec1), end(vec1), begin(vec2), begin(vec1),
		[](int a, int b){ return a + b; });

	println("Vector1: {:n}", vec1);
	println("Vector2: {:n}", vec2);
}
