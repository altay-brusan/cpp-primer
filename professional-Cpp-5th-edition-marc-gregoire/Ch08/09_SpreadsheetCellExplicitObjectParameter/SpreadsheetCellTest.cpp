/*
 * Chapter 8 - Explicit Object Parameter driver
 *
 * Call sites look identical to folder 08 - the explicit object parameter is invisible to
 * callers, it only changes the signature of the function being defined.
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
