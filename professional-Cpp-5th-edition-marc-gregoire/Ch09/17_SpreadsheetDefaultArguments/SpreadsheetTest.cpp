/*
 * Chapter 9 - Default Arguments (driver)
 *
 * Builds three Spreadsheets using zero, one, and two constructor arguments. All
 * three calls resolve to the same constructor declaration -
 * `Spreadsheet(size_t width = 100, size_t height = 100)` - with the missing
 * trailing parameters filled in from the defaults.
 */
#include "Spreadsheet.h"

using namespace std;

int main()
{
	Spreadsheet s1;
	Spreadsheet s2 { 5 };
	Spreadsheet s3 { 5, 6 };
}
