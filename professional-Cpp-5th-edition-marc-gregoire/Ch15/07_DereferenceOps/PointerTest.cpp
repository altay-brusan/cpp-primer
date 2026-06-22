/*
 * Chapter 15 - Using the Dereferencing Operators
 *
 * Driver for the Pointer smart-pointer template. It wraps an int and a SpreadsheetCell,
 * then uses *smartInt to read/write the pointee through operator* and smartCell->set() /
 * smartCell->getValue() through operator->. The const helper functions show that passing
 * the Pointer by reference-to-const selects the const operator* / operator-> overloads.
 */
#include "Pointer.h"
#include "SpreadsheetCell.h"
#include <print>

using namespace std;

void testConstPointerInt(const Pointer<int>& p)
{
	println("{} ", *p);
	// *p = 7;
}

void testConstPointerCell(const Pointer<SpreadsheetCell>& p)
{
	println("{} ", p->getValue());
	// p->set(5);
}

int main()
{
	Pointer<int> smartInt{ new int };
	*smartInt = 5; // Dereference the smart pointer.
	println("{} ", *smartInt);
	testConstPointerInt(smartInt);

	Pointer<SpreadsheetCell> smartCell{ new SpreadsheetCell };
	smartCell->set(5); // Dereference and member select the set() member function.
	println("{} ", smartCell->getValue());
	testConstPointerCell(smartCell);
}
