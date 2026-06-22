/*
 * Chapter 12 - Explicit Object Parameter: driver
 *
 * Same client code as sample 06 - the deducing-this implementation is a
 * drop-in replacement for the const/non-const pair. From the caller's
 * point of view nothing changed.
 */
#include "Grid.h"

int main()
{
	Grid<int> myIntGrid{ 2, 2 };
	Grid<double> myDoubleGrid;
	myIntGrid.at(1, 1) = 11;

	myDoubleGrid = myIntGrid;
	Grid<double> newDoubleGrid{ myIntGrid };
}
