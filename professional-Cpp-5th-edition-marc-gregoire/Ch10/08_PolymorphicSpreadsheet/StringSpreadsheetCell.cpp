/*
 * Chapter 10 - Polymorphic Spreadsheet (string cell impl)
 *
 * The matching free operator+ for two string cells. Concatenation, not
 * arithmetic.
 */
#include "StringSpreadsheetCell.h"

StringSpreadsheetCell operator+(const StringSpreadsheetCell& lhs,
	const StringSpreadsheetCell& rhs)
{
	StringSpreadsheetCell newCell;
	newCell.set(lhs.getString() + rhs.getString());
	return newCell;
}
