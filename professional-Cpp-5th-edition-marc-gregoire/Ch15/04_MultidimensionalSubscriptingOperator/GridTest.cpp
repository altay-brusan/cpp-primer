/*
 * Chapter 15 - Using the Multidimensional Subscripting Operator
 *
 * Driver that fills and prints a 4x4 Grid<int> using the two-index grid[x, y] syntax,
 * showing the C++23 multidimensional operator[] in action for both writing and reading
 * (with value_or() to handle empty optional cells).
 */
#include "Grid.h"
#include <print>
#include <cstddef>

using namespace std;

int main()
{
	Grid<int> myIntGrid{ 4, 4 };

	int counter{ 0 };
	for (size_t y{ 0 }; y < myIntGrid.getHeight(); ++y) {
		for (size_t x{ 0 }; x < myIntGrid.getWidth(); ++x) {
			myIntGrid[x, y] = ++counter;
		}
	}

	for (size_t y{ 0 }; y < myIntGrid.getHeight(); ++y) {
		for (size_t x{ 0 }; x < myIntGrid.getWidth(); ++x) {
			print("{:3} ", myIntGrid[x, y].value_or(0));
		}
		println("");
	}
}
