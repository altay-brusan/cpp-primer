/*
 * Chapter 8 - Array creation without a default constructor
 *
 * The two failing lines are intentionally left in to show the compiler error. Comment them
 * out, recompile, and the explicit per-element initialization further down does succeed.
 *
 * Key notes:
 *   - `SpreadsheetCell cells[3];` requires a default constructor.
 *   - The element-by-element form works because each slot is given its own constructor
 *     argument.
 */

#include "SpreadsheetCell.h"

int main()
{
	// Comment out these next two lines to test the third line
	SpreadsheetCell cells[3]; // FAILS compilation without a default constructor
	SpreadsheetCell* myCellp{ new SpreadsheetCell[10] }; // also FAILS

	// This line compiles without a default constructor - each slot is initialized explicitly.
	SpreadsheetCell cells[3]{ SpreadsheetCell{ 0 }, SpreadsheetCell{ 23 },
					SpreadsheetCell{ 41 } };
}
