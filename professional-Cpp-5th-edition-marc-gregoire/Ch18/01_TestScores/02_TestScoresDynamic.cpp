/*
 * Chapter 18 - Dynamic-Length vector with push_back()
 *
 * The same test-score normalizer, but built on a vector that grows on demand.
 * It starts empty (default constructor) and appends each entered score with
 * push_back(), which allocates space automatically. Input stops on -1, then
 * the scores are normalized and printed.
 *
 * Key notes:
 *   - Reads scores from cin, so it needs interactive input to run.
 */

#include <print>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int main()
{
	vector<double> doubleVector; // Create a vector with zero elements.

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
	for (auto& element : doubleVector) {
		element /= max;
		print("{} ", element);
	}
	println("");
}
