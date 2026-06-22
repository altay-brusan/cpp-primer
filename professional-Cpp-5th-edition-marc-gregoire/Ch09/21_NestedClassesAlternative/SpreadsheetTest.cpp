/*
 * Chapter 9 - Nested Classes, forward-declared alternative (driver)
 *
 * Identical exercise as folder 20. Choosing between the inline and the
 * forward-declared nested class form is a readability decision; usage code stays
 * the same.
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
