/*
 * Chapter 18 - Iterating a vector with Iterators
 *
 * Rewrites the test-score normalizer's output loop to use an explicit
 * vector<double>::iterator obtained from begin() and end(), advanced with
 * ++iter and dereferenced with the * operator to read and modify each element.
 * A commented-out variant shows the same loop simplified with auto.
 *
 * Key notes:
 *   - Reads scores from cin, so it needs interactive input to run.
 */

#include <print>
#include <vector>
#include <limits>
#include <iostream>

using namespace std;

int main()
{
	vector<double> doubleVector;

	// Initialize max to smallest number.
	double max{ -numeric_limits<double>::infinity() };

	for (size_t i{ 1 }; true; ++i) {
		double value;
		print("Enter score {} (-1 to stop): ", i);
		cin >> value;
		if (value == -1) {
			break;
		}
		doubleVector.push_back(value);
		if (value > max) {
			max = value;
		}
	}

	max /= 100.0;

	for (vector<double>::iterator iter{ begin(doubleVector) };
		iter != end(doubleVector); ++iter) {
		*iter /= max;
		print("{} ", *iter);
	}
	println("");

/*
	// Using auto keyword
	for (auto iter{ begin(doubleVector) };
		iter != end(doubleVector); ++iter) {
		*iter /= max;
		print("{} ", *iter);
	}
	println("");
*/
}
