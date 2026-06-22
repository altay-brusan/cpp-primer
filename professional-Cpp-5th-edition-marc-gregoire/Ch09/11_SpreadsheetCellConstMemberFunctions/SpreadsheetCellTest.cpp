/*
 * Chapter 9 - const Member Functions (driver)
 *
 * Demonstrates the practical effect of marking observers `const`:
 *   - Non-const member functions like `setString` are callable on the non-const
 *     `myCell`.
 *   - Through a `const SpreadsheetCell&` only the `const` overloads are reachable;
 *     the commented `setString` call would refuse to compile.
 */
#include "SpreadsheetCell.h"
#include <print>

using namespace std;

int main()
{
	SpreadsheetCell myCell { 5 };
	println("{}", myCell.getValue());       // OK
	myCell.setString("6");                  // OK

	const SpreadsheetCell& myCellConstRef{ myCell };
	println("{}", myCellConstRef.getValue()); // OK
	//myCellConstRef.setString("6"); // Compilation Error!
}
