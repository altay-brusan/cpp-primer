/*
 * Chapter 9 - Disallowing Assignment and Pass-by-Value (driver)
 *
 * This driver will not compile if the deleted copy operations are taken seriously.
 * `printSpreadsheet(Spreadsheet s)` needs to copy the argument, and `s1 = s2` needs
 * the copy assignment operator - both are deleted, so each line is a deliberate
 * error showing how `= delete` shuts the door on accidental copies.
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
}
