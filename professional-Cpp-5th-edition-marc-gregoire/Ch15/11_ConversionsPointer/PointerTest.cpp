/*
 * Chapter 15 - Using a Pointer in Boolean Expressions (operator void*)
 *
 * Driver that passes a null and a non-null Pointer<SpreadsheetCell> to process(), which
 * tests p against nullptr and 0, and uses p and !p directly in if statements - all enabled
 * by the operator void*() conversion.
 */
#include "Pointer.h"
#include "SpreadsheetCell.h"
#include <print>

using namespace std;

void process(const Pointer<SpreadsheetCell>& p)
{
	if (p != nullptr) { println("not nullptr"); }
	if (p != 0)       { println("not 0"); }
	if (p)            { println("not nullptr"); }
	if (!p)           { println("nullptr"); }
}

int main()
{
	Pointer<SpreadsheetCell> smartCell{ nullptr };
	process(smartCell);
	println("");

	Pointer<SpreadsheetCell> anotherSmartCell{ new SpreadsheetCell{5.0} };
	process(anotherSmartCell);
}
