/*
 * Chapter 9 - The Spreadsheet Class (driver)
 *
 * Exercises pass-by-value (which triggers the copy constructor) and assignment between
 * two Spreadsheets. With deep copying in place neither operation corrupts the source.
 */
#include "Spreadsheet.h"

void printSpreadsheet(Spreadsheet s)
{
	// code omitted for brevity
}

int main()
{
	{
		Spreadsheet s1{ 4, 3 };
		printSpreadsheet(s1);
	}

	{
		Spreadsheet s1{ 2, 2 }, s2{ 4, 3 };
		s1 = s2;
	}

	SpreadsheetCell cell { 2.2 };
}
