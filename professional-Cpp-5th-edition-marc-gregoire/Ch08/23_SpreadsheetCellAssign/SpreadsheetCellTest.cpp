/*
 * Chapter 8 - Assignment operator driver
 *
 * The first two statements are identical - the second just spells out what `=` desugars
 * to. The chained form works because operator= returns a reference to the left-hand side.
 * The final line triggers the self-assignment branch.
 */

#include "SpreadsheetCell.h"

int main()
{
	SpreadsheetCell myCell, anotherCell, aThirdCell;

	myCell = anotherCell = aThirdCell;                              // right-to-left chained assignment
	myCell.operator=(anotherCell.operator=(aThirdCell));            // desugared - same thing

	SpreadsheetCell cell{ 4 };
	cell = cell; // self-assignment - the `this == &rhs` guard short-circuits this
}
