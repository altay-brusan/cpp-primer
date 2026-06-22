/*
 * Chapter 8 - this Pointer demo
 *
 * Exercises the fixed `setValue()` - calling it now stores the value and feeds the cell to
 * `printCell()` via `*this`.
 */

#include "SpreadsheetCell.h"
#include <print>

using namespace std;

int main()
{
	SpreadsheetCell myCell, anotherCell;
	myCell.setValue(6);
	anotherCell.setString("3.2");

	println("cell 1: {}", myCell.getValue());
	println("cell 2: {}", anotherCell.getValue());
}
