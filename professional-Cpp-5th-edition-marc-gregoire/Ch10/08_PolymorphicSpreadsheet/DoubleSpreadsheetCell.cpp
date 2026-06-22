/*
 * Chapter 10 - Polymorphic Spreadsheet (numeric cell impl)
 *
 * Free-function operator+ for two numeric cells. Kept as a non-member because
 * the operands are symmetric (neither cell "owns" the operation) and member
 * operators would only allow conversion on the right-hand side.
 *
 * Note: the original file had `#pragma once` here - it's harmless but
 * meaningless in a .cpp; it belongs on headers.
 */
#include "DoubleSpreadsheetCell.h"

DoubleSpreadsheetCell operator+(const DoubleSpreadsheetCell& lhs,
	const DoubleSpreadsheetCell& rhs)
{
	DoubleSpreadsheetCell newCell;
	newCell.set(lhs.getValue() + rhs.getValue());
	return newCell;
}
