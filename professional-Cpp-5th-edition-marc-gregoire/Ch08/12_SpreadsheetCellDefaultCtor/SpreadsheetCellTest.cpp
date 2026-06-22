/*
 * Chapter 8 - Calling the Default Constructor
 *
 * Three ways to invoke the no-arg constructor: stack with no parens, stack with `{}`, and
 * free store via `new T{}` or `make_unique<T>()`. The "most vexing parse" cousin
 * `SpreadsheetCell myCell();` is intentionally NOT shown - that line would declare a
 * function, not an object.
 */

#include "SpreadsheetCell.h"
#include <print>
#include <memory>

using namespace std;

int main()
{
	SpreadsheetCell myCell;
	// Or
	// SpreadsheetCell myCell { }; // Calls the default constructor.
	myCell.setValue(6);
	println("cell 1: {}", myCell.getValue());

	auto smartCellp{ make_unique<SpreadsheetCell>() };

	// Or with a raw pointer (not recommended)
	SpreadsheetCell* myCellp{ new SpreadsheetCell{ } };
	// Or
	// SpreadsheetCell* myCellp{ new SpreadsheetCell };
	// Or
	// SpreadsheetCell* myCellp{ new SpreadsheetCell() };
	// ... use myCellp
	delete myCellp;    myCellp = nullptr;
}
