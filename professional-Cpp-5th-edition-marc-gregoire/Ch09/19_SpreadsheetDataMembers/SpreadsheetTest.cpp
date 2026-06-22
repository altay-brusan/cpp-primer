/*
 * Chapter 9 - Different Kinds of Data Members (driver)
 *
 * Builds two Spreadsheets, both linked to the same SpreadsheetApplication via the
 * reference data member. Each gets a fresh id from the shared `ms_counter`. Also
 * reads the class-scope constant `Spreadsheet::MaxHeight`.
 */
#include "Spreadsheet.h"
#include <print>

using namespace std;

int main()
{
	SpreadsheetApplication app;
	Spreadsheet s1 { 2, 3, app };
	Spreadsheet s2 { 3, 4, app };

	println("Maximum height is: {}", Spreadsheet::MaxHeight);
}
