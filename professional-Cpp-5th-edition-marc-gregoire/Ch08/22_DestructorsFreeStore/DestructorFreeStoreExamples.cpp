/*
 * Chapter 8 - Free-store destruction driver
 *
 * Two cells are allocated on the heap; only one is deleted. Run the program and count
 * the destructor messages: you will see exactly one. The second cell's destructor is
 * never called - this is a leak. The same code with `std::unique_ptr` (folder 06) would
 * clean both up automatically.
 */

#include "SpreadsheetCell.h"
#include <print>

using namespace std;

int main()
{
	SpreadsheetCell* cellPtr1{ new SpreadsheetCell{ 5 } };
	SpreadsheetCell* cellPtr2{ new SpreadsheetCell{ 6 } };

	println("cellPtr1: {}", cellPtr1->getValue());

	delete cellPtr1; // destroys cellPtr1
	cellPtr1 = nullptr;
} // cellPtr2 is NOT destroyed because delete was not called on it
