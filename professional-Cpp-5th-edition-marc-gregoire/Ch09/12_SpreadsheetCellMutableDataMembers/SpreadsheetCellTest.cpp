/*
 * Chapter 9 - mutable Data Members (driver)
 *
 * Exercises the read accessor; behind the scenes the mutable access counter ticks
 * up each time getValue() is called, even though getValue() itself is const.
 */
#include "SpreadsheetCell.h"
#include <print>

using namespace std;

int main()
{
	SpreadsheetCell myCell{ 5 };
	println("{}", myCell.getValue());
}
