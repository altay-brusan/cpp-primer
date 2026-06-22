/*
 * Chapter 8 - Objects on the Free Store
 *
 * The cell now lives on the heap. `new SpreadsheetCell{}` builds the object and hands back
 * a pointer; the arrow operator dereferences and member-accesses in one step; `delete`
 * tears it down and frees the storage. The follow-up `myCellp = nullptr;` is a hygiene
 * habit - a deleted pointer is a dangling pointer until you overwrite it.
 *
 * Key notes:
 *   - `new T{}` calls the default initialization just like `T x;` does on the stack.
 *   - `p->member` is shorthand for `(*p).member` - prefer the arrow form.
 *   - Every `new` needs a matching `delete`; smart pointers automate this (see folder 06).
 */

#include "SpreadsheetCell.h"
#include <print>

using namespace std;

int main()
{
	SpreadsheetCell* myCellp{ new SpreadsheetCell{ } };

	myCellp->setValue(3.7);
	println("cell 1: {} {}", myCellp->getValue(), myCellp->getString());
	delete myCellp;
	myCellp = nullptr;
}
