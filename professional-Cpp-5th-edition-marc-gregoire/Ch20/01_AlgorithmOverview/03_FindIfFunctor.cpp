/*
 * Chapter 20 - find_if with a Functor Predicate
 *
 * Same find_if() search for a perfect score as the previous sample, but the
 * predicate is supplied as a function object (functor). The PerfectScore class
 * defines a static function-call operator, and a pointer to that operator
 * (&PerfectScore::operator()) is handed to find_if() as the callback.
 *
 * Key notes:
 *   - Algorithm callbacks should be stateless; a static operator() makes that explicit.
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

class PerfectScore
{
public:
	static bool operator()(int num)
	{
		return num >= 100;
	}
};

int main()
{
	vector<int> myVector;
	populateContainer(myVector);

	auto endIt{ cend(myVector) };
	auto it{ find_if(cbegin(myVector), endIt, &PerfectScore::operator()) };
	if (it == endIt) {
		println("No perfect scores");
	}
	else {
		println("Found a \"perfect\" score of {}", *it);
	}
}
