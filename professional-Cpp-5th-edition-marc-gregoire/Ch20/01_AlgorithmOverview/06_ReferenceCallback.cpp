/*
 * Chapter 20 - Algorithm Callbacks and std::ref
 *
 * Shows that algorithms are allowed to copy their callbacks, which matters for
 * stateful callbacks. A mutable lambda isPerfectScore keeps a tally of how many
 * times it is invoked. Passing it to find_if() wrapped in std::ref() forces the
 * algorithm to use the same instance rather than a copy, so the tally and the
 * later explicit call all share one counter.
 *
 * Key notes:
 *   - Without ref(), find_if() would operate on a copy and the state changes
 *     would be lost; the commented-out line shows that alternative.
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

	auto isPerfectScore{ [tally = 0] (int i) mutable {
		println("{}", ++tally);  return i >= 100; } };

	auto endIt{ cend(myVector) };
	//auto it{ find_if(cbegin(myVector), endIt, isPerfectScore) };
	auto it{ find_if(cbegin(myVector), endIt, ref(isPerfectScore)) };
	if (it != endIt) { println("Found a \"perfect\" score of {}", *it); }
	println("---");
	isPerfectScore(1);
}
