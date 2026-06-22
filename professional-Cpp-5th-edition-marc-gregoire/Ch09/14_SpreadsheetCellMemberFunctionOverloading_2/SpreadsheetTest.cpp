/*
 * Chapter 9 - Overloading on const, private-helper variant (driver)
 *
 * Constructs both a mutable and a const Spreadsheet, then reads cell (1,1) from
 * each. Each call resolves to the matching overload, both of which forward to the
 * private getCellAtHelper.
 */
#include "Spreadsheet.h"

using namespace std;

int main()
{
	Spreadsheet sheet1{ 5, 6 };
	SpreadsheetCell& cell1{ sheet1.getCellAt(1, 1) };

	const Spreadsheet sheet2{ 5, 6 };
	const SpreadsheetCell& cell2{ sheet2.getCellAt(1, 1) };
}
