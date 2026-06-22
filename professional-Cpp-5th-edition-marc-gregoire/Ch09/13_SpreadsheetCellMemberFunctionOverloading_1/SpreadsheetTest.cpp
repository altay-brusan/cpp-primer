/*
 * Chapter 9 - Overloading Member Functions Based on const, first take (driver)
 *
 * Constructs both a mutable and a const Spreadsheet, then asks each for cell (1,1).
 * Compiler picks the matching `getCellAt` overload based on the const-ness of the
 * sheet - the result type differs accordingly.
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
