/*
 * Chapter 9 - Enumerated Types Inside Classes (driver)
 *
 * Sets a cell's color through the scoped enum then reads it back. The full path
 * `SpreadsheetCell::Color::Blue` is required because the enum is scoped.
 */
#include "SpreadsheetCell.h"

using namespace std;

int main()
{
	SpreadsheetCell myCell { 5 };
	myCell.setColor(SpreadsheetCell::Color::Blue);
	auto color{ myCell.getColor() };
}
