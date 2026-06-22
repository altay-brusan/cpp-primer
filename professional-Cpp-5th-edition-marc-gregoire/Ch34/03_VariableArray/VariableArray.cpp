/*
 * Chapter 34 - Variable-Length Arrays Are a Non-Standard Extension
 *
 * Declares a stack array whose size comes from a runtime variable. Variable-
 * length arrays (VLAs) are part of C but are NOT part of standard C++. Some
 * compilers (such as g++) accept them in C++ as a silent extension, but this
 * code is not portable: g++ with the -pedantic flag warns "ISO C++ forbids
 * variable length array", and MSVC rejects it outright. It illustrates how
 * relying on compiler extensions breaks cross-platform builds.
 */

int main()
{
	int i{ 4 };
	char myStackArray[i];  // Not a standard language feature!
}
