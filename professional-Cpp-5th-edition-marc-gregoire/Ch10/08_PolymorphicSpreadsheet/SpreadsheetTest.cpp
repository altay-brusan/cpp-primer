/*
 * Chapter 10 - Polymorphic Spreadsheet (driver)
 *
 * Shows the payoff of the abstract base class: a single `vector` can hold
 * heterogeneous cell types behind a `unique_ptr<SpreadsheetCell>` and call
 * `set()` / `getString()` polymorphically without caring which subclass is
 * inside.
 *
 * The bottom two blocks exercise the typed `operator+`. The second block also
 * demonstrates the implicit conversion: `stringCell + doubleCell` only works
 * because StringSpreadsheetCell has a converting ctor that accepts a
 * DoubleSpreadsheetCell, turning the second operand into a StringSpreadsheetCell.
 */
#include "DoubleSpreadsheetCell.h"
#include "StringSpreadsheetCell.h"
#include <print>
#include <vector>
#include <memory>

using namespace std;

int main()
{
	vector<unique_ptr<SpreadsheetCell>> cellArray;

	cellArray.push_back(make_unique<StringSpreadsheetCell>());
	cellArray.push_back(make_unique<StringSpreadsheetCell>());
	cellArray.push_back(make_unique<DoubleSpreadsheetCell>());

	cellArray[0]->set("hello");
	cellArray[1]->set("10");
	cellArray[2]->set("18");

	println("Vector: [{},{},{}]", cellArray[0]->getString(),
		cellArray[1]->getString(),
		cellArray[2]->getString());

	{
		DoubleSpreadsheetCell doubleCell;
		doubleCell.set(8.4);
		DoubleSpreadsheetCell result{ doubleCell + doubleCell };
		println("{}", result.getString());  // Prints 16.800000
	}

	{
		DoubleSpreadsheetCell doubleCell;
		doubleCell.set(8.4);
		StringSpreadsheetCell stringCell;
		stringCell.set("Hello ");
		StringSpreadsheetCell result{ stringCell + doubleCell };  // implicit conversion on RHS
		println("{}", result.getString());  // Prints Hello 8.400000
	}
}
