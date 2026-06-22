/*
 * Chapter 12 - Member Function Templates + Non-Type Parameters: driver
 *
 * Both `myDoubleGrid = myIntGrid` and `Grid<double> newDoubleGrid{myIntGrid}`
 * fire the templated converting operator= / ctor with E=int, WIDTH2=2,
 * HEIGHT2=2. The destination Grids are bigger; cells outside the source
 * range get reset to empty.
 */
#include "Grid.h"

using namespace std;

int main()
{
	Grid<int, 2, 2> myIntGrid;
	Grid<double, 4, 4> myDoubleGrid;
	myIntGrid.at(1, 1) = 11;

	myDoubleGrid = myIntGrid;
	Grid<double> newDoubleGrid{ myIntGrid };
}
