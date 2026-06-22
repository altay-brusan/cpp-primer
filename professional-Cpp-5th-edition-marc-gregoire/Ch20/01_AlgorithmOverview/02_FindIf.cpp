/*
 * Chapter 20 - find_if with a Function-Pointer Predicate
 *
 * Demonstrates std::find_if(), the predicate-based variant of find(). Instead of
 * matching a fixed value, find_if() calls a unary predicate on each element and
 * returns an iterator to the first element for which it returns true. Here the
 * predicate is the free function perfectScore(), passed as a function pointer, to
 * locate the first "perfect" test score (>= 100).
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

bool perfectScore(int num)
{
	return num >= 100;
}

int main()
{
	vector<int> myVector;
	populateContainer(myVector);

	auto endIt{ cend(myVector) };
	auto it{ find_if(cbegin(myVector), endIt, perfectScore) };
	if (it == endIt) {
		println("No perfect scores");
	} else {
		println("Found a \"perfect\" score of {}", *it);
	}
}
