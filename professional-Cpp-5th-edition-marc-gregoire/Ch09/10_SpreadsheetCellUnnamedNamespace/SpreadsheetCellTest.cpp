/*
 * Chapter 9 - Unnamed Namespace for Implementation Helpers (driver)
 *
 * Confirms the cell still works after pulling helpers into an unnamed namespace.
 * From the outside nothing has changed - the helpers are simply no longer reachable.
 */
#include "SpreadsheetCell.h"
#include <print>

using namespace std;

int main()
{
	SpreadsheetCell myCell { 5 };
	println("{}", myCell.getValue());
}
