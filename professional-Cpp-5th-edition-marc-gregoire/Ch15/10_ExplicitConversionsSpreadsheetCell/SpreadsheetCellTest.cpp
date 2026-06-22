/*
 * Chapter 15 - Using Explicit Conversion Operators
 *
 * Driver that evaluates double d1{ cell + 3.4 }. This line would be ambiguous with a
 * non-explicit operator double(); because the conversion operator is explicit, the
 * compiler converts 3.4 to a SpreadsheetCell and does SpreadsheetCell addition, then the
 * result is used to initialize d1.
 */
#include "SpreadsheetCell.h"
#include <print>

using namespace std;

int main()
{
	SpreadsheetCell cell{ 6.6 };

	double d1{ cell + 3.4 };
	println("{}", d1);
}
