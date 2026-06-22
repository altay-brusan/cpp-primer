/*
 * Chapter 8 - The this Pointer (ambiguous demo)
 *
 * Run this and the printed numbers will not match the values that were set - the broken
 * `setValue()` is the reason. The fix arrives in folder 08.
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
