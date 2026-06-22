/*
 * Chapter 15 - Using Conversion Operators
 *
 * Driver that converts a SpreadsheetCell to a double (double d1{ cell }) via
 * operator double(), and to a std::string via operator std::string() using both
 * assignment syntax (string str1 = cell;) and an explicit static_cast<string>(cell).
 */
#include "SpreadsheetCell.h"
#include <print>

using namespace std;

int main()
{
	SpreadsheetCell cell{ 1.23 };
	
	double d1{ cell };
	println("{}", d1);

	string str1 = cell;
	println("{}", str1);

	string str2{ static_cast<string>(cell) };
	println("{}", str2);
}
