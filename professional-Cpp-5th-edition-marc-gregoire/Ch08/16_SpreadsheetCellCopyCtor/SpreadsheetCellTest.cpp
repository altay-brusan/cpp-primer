/*
 * Chapter 8 - Calling the Copy Constructor Explicitly
 *
 * `SpreadsheetCell myCell2 { myCell1 };` is an initialization, and initialization with an
 * existing object invokes the copy constructor. After this line, `myCell1` and `myCell2`
 * hold the same stored value but are independent objects.
 */

#include "SpreadsheetCell.h"
#include <print>

using namespace std;

int main()
{
	SpreadsheetCell myCell1{ 4 };
	SpreadsheetCell myCell2{ myCell1 };
	// myCell2 has the same values as myCell1

	println("Cell 1: {}", myCell1.getValue());
	println("Cell 2: {}", myCell2.getValue());
}
