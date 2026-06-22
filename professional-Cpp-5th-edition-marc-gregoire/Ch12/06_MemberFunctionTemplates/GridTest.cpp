/*
 * Chapter 12 - Member Function Templates: driver
 *
 * Cross-type copy and assignment between a `Grid<int>` and a `Grid<double>`.
 * Both call sites are using the *templated* converting members - the
 * non-templated copy ctor/operator= only handle the same-T case.
 */
#include "Grid.h"

int main()
{
	Grid<int> myIntGrid{ 2, 2 };
	Grid<double> myDoubleGrid;
	myIntGrid.at(1, 1) = 11;

	myDoubleGrid = myIntGrid;                  // template operator= for E=int
	Grid<double> newDoubleGrid{ myIntGrid };   // template copy ctor for E=int
}
