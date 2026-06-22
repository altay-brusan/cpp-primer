/*
 * Chapter 34 - C and C++ Are Not Identical: Reserved Words
 *
 * This is C source, not C++. It uses "class" as a variable name, which is legal
 * in C (where class has no special meaning) but is a reserved keyword in C++.
 * It demonstrates a typical porting error encountered when moving C code into a
 * C++ compiler: the fix is simply to rename the identifier. It must be built
 * with a C compiler; a C++ compiler rejects it.
 */

#include <stdio.h>

int main()
{
	int class = 1; // Compiles in C, not C++
	printf("class is %d\n", class);
}
