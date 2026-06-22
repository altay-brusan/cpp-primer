/*
 * Chapter 15 - Using Unary and Increment Operators
 *
 * Driver that exercises the overloaded operators. It first shows the built-in unary plus
 * and unary minus on ints, then constructs SpreadsheetCells and applies unary minus
 * (operator-()) and both postfix (c1++) and prefix (++c2) increment to demonstrate that
 * the class now behaves like a built-in numeric type.
 */
#include "SpreadsheetCell.h"

using namespace std;

int main()
{
	int i, j{ 4 };
	i = -j; // Unary minus
	i = +i; // Unary plus
	j = +(-i); // Apply unary plus to the result of applying unary minus to i.
	j = -(-i); // Apply unary minus to the result of applying unary minus to i.

	i = i + 1;
	i += 1;
	++i;
	i++;

	SpreadsheetCell c1{ 4 };
	SpreadsheetCell c2{ 4 };
	SpreadsheetCell c3{ -c1 };
	c1++;
	++c2;
}
