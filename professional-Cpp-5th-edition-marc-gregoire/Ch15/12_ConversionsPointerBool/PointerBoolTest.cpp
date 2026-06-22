/*
 * Chapter 15 - Using operator bool and Its Pitfalls
 *
 * Driver for the operator bool() smart pointer. process() tests p != 0, p, and !p (the
 * p != nullptr line is commented out because it would not compile with a bool conversion).
 * main() also shows the surprising int i{ anotherSmartCell }, where the Pointer converts to
 * bool and then promotes to int - the unwanted behavior that argues against operator bool.
 */
#include "PointerBool.h"
#include "SpreadsheetCell.h"
#include <print>
using namespace std;

void process(Pointer<SpreadsheetCell>& p)
{
	// if (p != nullptr) { println("not nullptr"); }  // Error
	if (p != 0)          { println("not 0"); }
	if (p)               { println("not nullptr"); }
	if (!p)              { println("nullptr"); }
}

int main()
{
	Pointer<SpreadsheetCell> smartCell{ nullptr };
	process(smartCell);
	println("");

	Pointer<SpreadsheetCell> anotherSmartCell{ new SpreadsheetCell{ 5.0 } };
	process(anotherSmartCell);

	int i{ anotherSmartCell }; // Converts Pointer to bool to int.
	println("{}", i);
}
