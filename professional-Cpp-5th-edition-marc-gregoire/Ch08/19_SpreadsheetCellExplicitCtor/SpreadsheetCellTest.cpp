/*
 * Chapter 8 - Effects of `explicit`
 *
 * `myCell = 5;` still compiles because the double-arg constructor is not `explicit`. The
 * line `myCell = "6"sv;` will fail to compile against this header - that is the whole
 * demonstration. Either remove `explicit` in the header or change the line to
 * `myCell = SpreadsheetCell { "6"sv };` to see it build.
 */

#include "SpreadsheetCell.h"
#include <print>
#include <string_view>

using namespace std;

int main()
{
	SpreadsheetCell myCell{ 4 };
	myCell = 5;             // OK - double ctor is implicit (not explicit)
	myCell = "6"sv; // A string_view literal (see Chapter 2).  // BLOCKED by `explicit` on the string_view ctor

	println("Cell: {}", myCell.getValue());
}
