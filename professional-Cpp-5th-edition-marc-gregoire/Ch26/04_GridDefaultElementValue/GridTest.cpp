/*
 * Chapter 26 - Supplying a Non-type Template Argument
 *
 * Creates Grid<int> (default initial value 0) and Grid<int, 10> (initial value
 * 10) to show an integer passed as a non-type template argument. The commented
 * line illustrates that an object such as a SpreadsheetCell cannot be used as a
 * non-type template argument.
 */

#include "Grid.h"
#include "SpreadsheetCell.h"

int main()
{
	Grid<int> myIntGrid;		// Initial value is int{}, i.e., 0
	Grid<int, 10> myIntGrid2;	// Initial value is 10

	myIntGrid.at(1, 2) = 3;

	SpreadsheetCell defaultCell;
	//Grid<SpreadsheetCell, defaultCell> mySpreadsheet; // WILL NOT COMPILE
}
