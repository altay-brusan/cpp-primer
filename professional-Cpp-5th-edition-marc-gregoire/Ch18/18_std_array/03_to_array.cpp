/*
 * Chapter 18 - std::to_array()
 *
 * C++20's std::to_array() converts a C-style array (or braced list) into a
 * std::array, copy-initializing the elements and deducing both the element type
 * and length. Works for one-dimensional arrays only. Produces no output.
 */

#include <print>
#include <array>

using namespace std;

int main()
{
	auto arr1{ to_array({ 11, 22, 33 }) }; // Type is array<int, 3>

	double carray[]{ 9, 8, 7, 6 };
	auto arr2{ to_array(carray) };         // Type is array<double, 4>
}