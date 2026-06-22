/*
 * Chapter 9 - Nested Classes (driver)
 *
 * Cells outside the Spreadsheet must be spelled `Spreadsheet::Cell`. The driver
 * builds a Spreadsheet, then a few free-standing Cells using that qualified name.
 */
#include "Spreadsheet.h"
#include <print>

using namespace std;

int main()
{
	SpreadsheetApplication theApp;
	Spreadsheet s1 { 5, 6, theApp };

	Spreadsheet::Cell c1 { 4 }, c2 { 5 };
	Spreadsheet::Cell c3 { c1 };
	c2 = c3;

	println("{}", c1.getValue());

	s1.getId();
}
