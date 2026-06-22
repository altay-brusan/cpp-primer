/*
 * Chapter 18 - vector initializer_list Constructor
 *
 * Constructs a vector<int> directly from an initializer_list of values,
 * { 1, 2, 3, 4, 5, 6 }, supplying the initial elements at construction.
 */

#include <print>
#include <vector>

using namespace std;

int main()
{
	vector<int> intVector({ 1, 2, 3, 4, 5, 6 });
	println("Vector elements: {}", intVector);
}
