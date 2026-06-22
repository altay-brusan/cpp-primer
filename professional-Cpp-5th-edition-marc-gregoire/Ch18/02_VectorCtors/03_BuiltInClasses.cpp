/*
 * Chapter 18 - vector of a Built-in Library Class
 *
 * Shows that vector elements can be objects of standard classes: a
 * vector<string> of 10 elements is fill-constructed, each set to "hello".
 */

#include <print>
#include <vector>
#include <string>

using namespace std;

int main()
{
	vector<string> stringVector(10, "hello");
	println("Vector elements: {}", stringVector);
}
