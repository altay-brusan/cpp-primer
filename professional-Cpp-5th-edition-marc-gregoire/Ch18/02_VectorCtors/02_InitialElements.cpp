/*
 * Chapter 18 - vector Fill Constructor
 *
 * Uses the vector(count, value) constructor to create a vector of 10 ints all
 * initialized to 100. Note the round-parenthesis call syntax: with braces,
 * { 10, 100 } would instead create a two-element vector.
 */

#include <print>
#include <vector>

using namespace std;

int main()
{
	vector<int> intVector(10, 100); // Creates a vector of 10 ints with value 100
	println("Vector elements: {}", intVector);
}
