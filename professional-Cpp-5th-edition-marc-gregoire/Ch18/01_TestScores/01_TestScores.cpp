/*
 * Chapter 18 - vector as a Fixed-Length Array
 *
 * Demonstrates using std::vector like a classic C-style array. A vector of 10
 * doubles is created with the size constructor, then accessed with operator[]
 * and size() in a counting loop. The program reads ten test scores from the
 * user, normalizes them so the highest becomes 100, and prints the adjusted
 * values via a range-based for loop using auto& so elements can be modified
 * in place.
 *
 * Key notes:
 *   - operator[] does no bounds checking; use at() if you want an out_of_range
 *     exception on a bad index.
 *   - Reads scores from cin, so it needs interactive input to run.
 */

#include <print>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int main()
{
	vector<double> doubleVector(10); // Create a vector of 10 doubles.

	// Initialize max to smallest number.
	double max{ -numeric_limits<double>::infinity() };

	for (size_t i{ 0 }; i < doubleVector.size(); ++i) {
		print("Enter score {}: ", i + 1);
		cin >> doubleVector[i];
		if (doubleVector[i] > max) {
			max = doubleVector[i];
		}
	}

	max /= 100.0;
	for (auto& element : doubleVector) {
		element /= max;
		print("{} ", element);
	}
	println("");
}
