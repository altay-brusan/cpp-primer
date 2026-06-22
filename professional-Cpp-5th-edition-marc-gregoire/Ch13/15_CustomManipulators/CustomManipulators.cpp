/*
 * Chapter 13 - Writing a Custom Manipulator
 *
 * A manipulator with no arguments is just a function taking and returning an
 * ostream&. Here tab() writes a '\t' and returns the stream, so it can be used
 * inline in a << chain exactly like endl.
 */

#include <iostream>

using namespace std;

// Custom tab manipulator.
ostream& tab(ostream& stream)
{
	return stream << '\t';
}

int main()
{
	cout << "Test" << tab << "!" << endl;
}
