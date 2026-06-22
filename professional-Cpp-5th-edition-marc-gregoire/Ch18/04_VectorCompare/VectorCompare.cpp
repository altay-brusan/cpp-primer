/*
 * Chapter 18 - Comparing vectors
 *
 * The Standard Library provides the six comparison operators for vector. Two
 * vectors are equal when they have the same size and all corresponding elements
 * are equal; operator< compares them lexicographically. Comparing with ==
 * requires the elements to support ==; comparing with < requires <.
 */

#include <print>
#include <vector>

using namespace std;

int main()
{
	vector<int> vectorOne(10);
	vector<int> vectorTwo(10);

	if (vectorOne == vectorTwo) {
		println("equal!");
	} else {
		println("not equal!");
	}

	vectorOne[3] = 50;

	if (vectorOne < vectorTwo) {
		println("vectorOne is less than vectorTwo");
	} else {
		println("vectorOne is not less than vectorTwo");
	}
}
