/*
 * Chapter 32 - The Copy-and-Swap Idiom (driver)
 *
 * Minimal driver that creates two CopyAndSwap instances and assigns one to the other,
 * exercising the copy assignment operator implemented with the copy-and-swap idiom.
 */
#include "CopyAndSwap.h"

int main()
{
	CopyAndSwap myFirstInstance;
	CopyAndSwap mySecondInstance;
	mySecondInstance = myFirstInstance;
}
