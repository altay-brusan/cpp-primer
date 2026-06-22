/*
 * Chapter 13 - Output Basics
 *
 * The starting point for output streams: the << operator. It writes the C++
 * basic types (int, char), std::string, and C-style strings to cout, the
 * built-in stream for the console. Because operator<< returns a reference to
 * the stream, calls can be "chained" to output several pieces of data in one
 * statement.
 *
 * Key notes:
 *   - std::endl starts a new line AND flushes the buffer; '\n' only starts a
 *     new line. Prefer '\n' in performance-critical code to avoid extra flushes.
 */

#include <iostream>
#include <string>

using namespace std;

int main()
{
	int i{ 7 };
	cout << i << endl;

	char ch{ 'a' };
	cout << ch << endl;

	string myString{ "Hello World." };
	cout << myString << endl;


	int j{ 11 };
	cout << "The value of j is " << j << "!" << endl;


	cout << "Line 1" << endl << "Line 2" << endl << "Line 3" << endl;
}
