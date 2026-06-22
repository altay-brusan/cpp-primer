/*
 * Chapter 18 - vector Default Constructor
 *
 * The default constructor creates a vector with zero elements. Here an empty
 * vector<int> is created and printed using C++23 range formatting.
 */

#include <print>
#include <vector>

using namespace std;

int main()
{
	vector<int> intVector; // Creates a vector of ints with zero elements
	println("Vector elements: {}", intVector);
}
