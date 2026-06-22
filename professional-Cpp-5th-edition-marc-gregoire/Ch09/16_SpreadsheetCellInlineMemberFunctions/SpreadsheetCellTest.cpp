/*
 * Chapter 9 - inline Member Functions (driver)
 *
 * Trivial usage of the inline getter so the compiler has something to actually
 * inline. Behavioural output is identical to the non-inline version.
 */
#include "SpreadsheetCell.h"
#include <print>

using namespace std;

int main()
{
	SpreadsheetCell myCell { 5 };
	println("{}", myCell.getValue());
}
