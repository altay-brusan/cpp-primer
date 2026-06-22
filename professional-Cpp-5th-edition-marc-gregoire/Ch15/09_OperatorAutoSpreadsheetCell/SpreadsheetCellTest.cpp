/*
 * Chapter 15 - Using operator auto Conversions
 *
 * Driver identical in use to sample 08: it converts a SpreadsheetCell to double and to
 * string. Here the double conversion is produced by operator auto() (deduced type) rather
 * than an explicitly typed operator double().
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
