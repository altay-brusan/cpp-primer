/*
 * Chapter 8 - Free Store with the deref-and-dot form
 *
 * Same allocation pattern as folder 04, only the member-access syntax is verbose. The two
 * forms are equivalent; this file exists to show why `->` was invented.
 *
 * Key notes:
 *   - `(*myCellp).setValue(3.7)` is the long-hand for `myCellp->setValue(3.7)`.
 *   - The parentheses around `*myCellp` are required - dot binds tighter than dereference.
 */

#include "SpreadsheetCell.h"
#include <print>

using namespace std;

int main()
{
	SpreadsheetCell* myCellp{ new SpreadsheetCell{ } };

	(*myCellp).setValue(3.7);
	println("cell 1: {} {}", (*myCellp).getValue(), (*myCellp).getString());
	delete myCellp;
	myCellp = nullptr;
}
