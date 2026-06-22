/*
 * Chapter 18 - Uniform Initialization and CTAD for vector
 *
 * Three equivalent ways to create a vector of six ints: with = braces, with
 * direct braces, and with class template argument deduction (CTAD) where the
 * element type is deduced and the <int> is omitted entirely.
 */

#include <print>
#include <vector>

using namespace std;

int main()
{
	vector<int> intVector1 = { 1, 2, 3, 4, 5, 6 };
	vector<int> intVector2{ 1, 2, 3, 4, 5, 6 };
	vector intVector3{ 1, 2, 3, 4, 5, 6 };

	println("Vector 1 elements: {}", intVector1);
	println("Vector 2 elements: {}", intVector2);
	println("Vector 3 elements: {}", intVector3);
}
