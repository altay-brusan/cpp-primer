/*
 * Chapter 12 - Non-Type Template Parameters: driver
 *
 * Three ways to pass a non-type argument:
 *   - Literal:                  Grid<int, 10, 10>
 *   - const size_t variable:    height = 10; Grid<int, 10, height>
 *   - constexpr function:       Grid<double, 2, getHeight()>
 *
 * All three are *constant expressions* - the compiler can evaluate them
 * during translation. A plain `size_t height = 10;` (without const) would
 * NOT work because it isn't a constant expression.
 */
#include "Grid.h"
#include <print>

using namespace std;

constexpr size_t getHeight()
{
	return 10;
}

int main()
{
	Grid<int, 10, 10> myGrid;
	Grid<int, 10, 10> anotherGrid;

	myGrid.at(2, 3) = 42;
	anotherGrid = myGrid;

	println("{}", anotherGrid.at(2, 3).value_or(0));

	const size_t height{ 10 };
	Grid<int, 10, height> testGrid;

	Grid<double, 2, getHeight()> myDoubleGrid;
}
