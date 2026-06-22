/*
 * Chapter 9 - Operator Overloading: First Attempt with add() (driver)
 *
 * Builds two cells and combines them with `myCell.add(anotherCell)`. Compare with
 * the next folder's `myCell + anotherCell` to see why operator syntax is worth
 * the effort.
 */
#include "SpreadsheetCell.h"
#include <print>

using namespace std;

int main()
{
	SpreadsheetCell myCell { 4 } , anotherCell {5 };
	SpreadsheetCell aThirdCell{ myCell.add(anotherCell) };
	auto aFourthCell{ aThirdCell.add(anotherCell) };
	println("{}", aThirdCell.getValue());
}
