/*
 * Chapter 12 - Class Templates (first version): driver
 *
 * Each line in main() is a worked example from the chapter:
 *   - `Grid<int>` with default size, `Grid<double>{11,11}` with explicit size.
 *   - `Grid<SpreadsheetCell>` - a user-defined type as T.
 *   - `Grid<const char*>` - a pointer type as T (works because optional<T> works for it).
 *   - `Grid<vector<int>>` - nested templates; note the `>>` is fine since C++11.
 *   - `make_unique<Grid<int>>(2,2)` - heap-allocated specialization.
 *
 * The commented `Grid test;` / `Grid<> test;` lines highlight that you
 * must supply a template argument (no defaults are in play yet - the
 * 04_GridNonTypeDefault sample shows defaults).
 *
 * At the bottom: `template class Grid<string>;` is an *explicit class
 * template instantiation*. It forces the compiler to emit every member
 * function body for `Grid<string>` in this TU, regardless of whether
 * they're called. Pragma use: keeping template bodies in a .cpp (rare).
 */
#include "Grid.h"
#include "SpreadsheetCell.h"
#include <memory>
#include <vector>
#include <string>

using namespace std;

void processIntGrid(Grid<int>& /*grid*/)
{
	// Body omitted for brevity
}

int main()
{
	Grid<int> myIntGrid; // Declares a grid that stores ints,
						 // using default arguments for the constructor.
	Grid<double> myDoubleGrid{ 11, 11 }; // Declares an 11x11 Grid of doubles.

	myIntGrid.at(0, 0) = 10;
	int x{ myIntGrid.at(0, 0).value_or(0) };

	Grid<int> grid2{ myIntGrid };  // Copy constructor
	Grid<int> anotherIntGrid;
	anotherIntGrid = grid2;      // Assignment operator

	//Grid test;   // WILL NOT COMPILE
	//Grid<> test; // WILL NOT COMPILE

	processIntGrid(myIntGrid);

	Grid<SpreadsheetCell> mySpreadsheet;
	SpreadsheetCell myCell{ 1.234 };
	mySpreadsheet.at(3, 4) = myCell;

	Grid<const char*> myStringGrid;
	myStringGrid.at(2, 2) = "hello";

	Grid<vector<int>> gridOfVectors;
	vector<int> myVector{ 1, 2, 3, 4 };
	gridOfVectors.at(5, 6) = myVector;

	auto myGridOnFreeStore { make_unique<Grid<int>>(2, 2) }; // 2x2 Grid on the free store.
	myGridOnFreeStore->at(0, 0) = 10;
	int x2 { myGridOnFreeStore->at(0, 0).value_or(0) };
}

// Explicit class template instantiation.
template class Grid<string>;
