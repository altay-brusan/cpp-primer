/*
 * Chapter 8 - Stack destruction order driver
 *
 * Notice the two nested blocks and how the destructor lines arrive: the inner-most local
 * dies first, and within a single block locals die in reverse declaration order. Run this
 * once and trace the output against the source - that pattern is the rule for every
 * stack object in C++.
 */

#include "SpreadsheetCell.h"
#include <print>

using namespace std;

int main()
{
	SpreadsheetCell myCell{ 5 };

	if (myCell.getValue() == 5) {
		SpreadsheetCell anotherCell{ 6 };
	} // anotherCell is destroyed as this block ends

	println("myCell: {}", myCell.getValue());

	{
		SpreadsheetCell myCell2{ 4 };
		SpreadsheetCell anotherCell2{ 5 }; // myCell2 constructed before anotherCell2
	} // anotherCell2 destroyed before myCell2
} // myCell is destroyed as this block ends
