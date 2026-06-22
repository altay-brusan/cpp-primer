/*
 * Chapter 8 - Free Store with Smart Pointers
 *
 * Compare this to folder 04 - the only thing that changed is the allocation mechanism, yet
 * the explicit `delete` and `= nullptr` have both disappeared. The unique_ptr handles
 * destruction at scope exit, including in the presence of exceptions thrown later.
 *
 * Key notes:
 *   - `std::make_unique<T>(args...)` forwards the arguments to T's constructor; no
 *     parentheses means the default constructor is used.
 *   - Reach members with `->` just like a raw pointer.
 *   - This is the recommended way to own a heap object in modern C++.
 */

#include "SpreadsheetCell.h"
#include <print>
#include <memory>

using namespace std;

int main()
{
	auto myCellp{ make_unique<SpreadsheetCell>() };
	// Equivalent to:
	// unique_ptr<SpreadsheetCell> myCellp{ new SpreadsheetCell{ } };
	
	myCellp->setValue(3.7);
	println("cell 1: {} {}", myCellp->getValue(), myCellp->getString());
}
