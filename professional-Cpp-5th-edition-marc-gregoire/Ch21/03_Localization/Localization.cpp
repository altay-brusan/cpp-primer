/*
 * Chapter 21 - Localizing String Literals
 *
 * Illustrates why you should never compose sentences by concatenating string
 * literals around runtime values. The two wcout statements build the same "N bytes
 * read from file" message in different languages, showing that translation often
 * requires reordering the words, which hard-coded concatenation cannot express.
 * The proper solution is to load a full, reorderable format string from a resource
 * table and substitute the values into it.
 */

#include <string>
#include <iostream>

using namespace std;

int main()
{
	unsigned n{ 5 };
	wstring filename{ L"file1.txt" };
	wcout << n << L" bytes read from " << filename << endl;
	wcout << n << L" Bytes aus " << filename << L" gelezen" << endl;
}