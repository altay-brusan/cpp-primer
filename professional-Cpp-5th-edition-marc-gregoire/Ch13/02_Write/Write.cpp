/*
 * Chapter 13 - write(): Raw Character-Array Output
 *
 * write() is a raw output method: instead of an object with defined output
 * behavior, it takes a character array and a length and emits those bytes as
 * is, with no formatting. Here it writes a C-style string to cout, using
 * strlen() to supply the count.
 */

#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	const char* test{ "hello there" };
	cout.write(test, strlen(test));
}
