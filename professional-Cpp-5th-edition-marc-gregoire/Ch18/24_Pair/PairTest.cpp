/*
 * Chapter 18 - The pair Utility
 *
 * std::pair groups two values of possibly different types, reachable through
 * the public first and second members, with all comparison operators defined
 * lexicographically. The example shows construction, direct member assignment,
 * copying, comparisons, and three ways to build a pair: make_pair(), auto, and
 * CTAD.
 */

#include <print>
#include <string>
#include <utility>

using namespace std;

int main()
{
	// Two-argument constructor and default constructor
	pair<string, int> myPair{ "hello", 5 };
	pair<string, int> myOtherPair;

	// Can assign directly to first and second
	myOtherPair.first = "hello";
	myOtherPair.second = 6;

	// copy constructor
	pair<string, int> myThirdPair{ myOtherPair };

	// operator<
	if (myPair < myOtherPair) {
		println("myPair is less than myOtherPair");
	} else {
		println("myPair is greater than or equal to myOtherPair");
	}

	// operator==
	if (myOtherPair == myThirdPair) {
		println("myOtherPair is equal to myThirdPair");
	} else {
		println("myOtherPair is not equal to myThirdPair");
	}

	pair<int, double> pair1{ make_pair(5, 10.10) };
	auto pair2{ make_pair(5, 10.10) };
	pair pair3{ 5, 10.10 };
}
