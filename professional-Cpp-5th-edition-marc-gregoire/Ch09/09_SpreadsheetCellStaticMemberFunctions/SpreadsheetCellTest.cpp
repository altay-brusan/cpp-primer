/*
 * Chapter 9 - static Member Functions (driver)
 *
 * Trivial sanity check that a SpreadsheetCell still constructs and reads back its
 * value after the conversion helpers were moved to static. The statics are private
 * here, so they cannot be called from main; they live inside the cell's own
 * constructors and accessors.
 */
#include "SpreadsheetCell.h"
#include <print>

using namespace std;

int main()
{
	SpreadsheetCell myCell { 5 };
	println("{}", myCell.getValue());
}
