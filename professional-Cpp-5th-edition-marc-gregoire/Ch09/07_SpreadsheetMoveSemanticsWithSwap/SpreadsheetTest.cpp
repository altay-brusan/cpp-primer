/*
 * Chapter 9 - Move Constructor and Move Assignment in Terms of Swap (driver)
 *
 * Same scenarios as folder 04/06. The output should still show move construction on
 * vector growth and move assignment on `s = createObject()`, confirming the
 * swap-based implementation behaves identically from the outside.
 */
#include "Spreadsheet.h"
#include <print>
#include <vector>

using namespace std;

Spreadsheet createObject()
{
	return Spreadsheet { 3, 2 };
}

int main()
{
	vector<Spreadsheet> vec;
	for (size_t i{ 0 }; i < 2; ++i) {
		println("Iteration {}", i);
		vec.push_back(Spreadsheet { 100, 100 });
		println("");
	}

	Spreadsheet s { 2, 3 };
	s = createObject();

	println("");

	Spreadsheet s2 { 5, 6 };
	s2 = s;
}
