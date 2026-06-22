/*
 * Chapter 20 - Searching with the find Algorithm
 *
 * Demonstrates the std::find() non-modifying algorithm. The user fills a vector,
 * then repeatedly looks up values: find() scans the iterator range [cbegin, cend)
 * and returns an iterator to the first matching element, or the supplied end
 * iterator if no match exists. The lookup uses a C++17 if-statement with
 * initializer to declare the result iterator and test it in one statement.
 *
 * Key notes:
 *   - find() returns the end iterator passed in the call, not necessarily the
 *     container's own end - here they are the same.
 *   - Runs in linear time; containers like map and set offer faster find() methods.
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
	vector<int> myVector;
	populateContainer(myVector);

	while (true) {
		print("Enter a number to lookup (0 to stop): ");
		int number;
		cin >> number;
		if (number == 0) {
			break;
		}
		auto endIt{ cend(myVector) };
		//auto it{ find(cbegin(myVector), endIt, number) };
		//if (it == endIt) {
		if (auto it{ find(cbegin(myVector), endIt, number) }; it == endIt) {
			println("Could not find {}", number);
		} else {
			println("Found {}", *it);
		}
	}
}
