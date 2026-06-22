/*
 * Chapter 8 - Driver for the ctor-initializer version of SpreadsheetCell
 *
 * Behaviour is identical to folder 13 - the change is internal. The output is the same;
 * the construction path is more direct.
 */

#include "SpreadsheetCell.h"
#include <print>
#include <memory>

using namespace std;

int main()
{
	SpreadsheetCell myCell;
	myCell.setValue(6);
	println("cell 1: {}", myCell.getValue());

	auto smartCellp{ make_unique<SpreadsheetCell>() };
	// Or with a raw pointer (not recommended)
	SpreadsheetCell* myCellp{ new SpreadsheetCell{ } };
	// Or
	// SpreadsheetCell* myCellp{ new SpreadsheetCell };
	// ... use myCellp
	delete myCellp;    myCellp = nullptr;
}
