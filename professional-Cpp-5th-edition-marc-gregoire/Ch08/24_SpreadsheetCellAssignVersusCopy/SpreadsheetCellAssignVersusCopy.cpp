/*
 * Chapter 8 - Copy vs. Assignment, side by side
 *
 * Read this driver top to bottom. The first three lines all construct a fresh cell -
 * which means they all invoke the copy constructor, even the one that uses `=`. The
 * fourth line targets an object that is already alive, so that one calls operator=. The
 * string-side examples below show the same pattern with `std::string`: a temporary
 * returned by getString() is consumed either by a copy constructor (when initializing
 * `s2`) or by an assignment operator (when overwriting `s1`).
 */

#include "SpreadsheetCell.h"
#include <string>

using namespace std;

int main()
{
	SpreadsheetCell myCell{ 5 };
	SpreadsheetCell anotherCell { myCell };       // copy constructor - looks like a declaration
	SpreadsheetCell aThirdCell = myCell;          // ALSO copy constructor - declaration with `=`
	anotherCell = myCell; // Calls operator= for anotherCell.  // assignment - anotherCell already exists

	SpreadsheetCell myCell2{ 5 };
	string s1;
	s1 = myCell2.getString();                     // operator= on s1 (s1 already constructed)

	SpreadsheetCell myCell3{ 5 };
	string s2 = myCell3.getString();              // copy ctor for s2 (subject to copy elision)
}
