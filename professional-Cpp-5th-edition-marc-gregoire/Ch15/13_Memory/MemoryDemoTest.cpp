/*
 * Chapter 15 - Exercising Overloaded new and delete
 *
 * Driver that allocates and frees MemoryDemo objects in several ways - single, array,
 * nothrow single/array, and the extra-int form new(5) - so the console output shows which
 * overloaded operator new and operator delete fire for each new-/delete-expression.
 */
#include "MemoryDemo.h"

using namespace std;

int main()
{
	MemoryDemo* mem{ new MemoryDemo{} };
	delete mem;

	mem = new MemoryDemo[10];
	delete [] mem;

	mem = new (nothrow) MemoryDemo{};
	delete mem;

	mem = new (nothrow) MemoryDemo[10];
	delete [] mem;

	MemoryDemo* memp{ new(5) MemoryDemo{} };
	delete memp;
}
