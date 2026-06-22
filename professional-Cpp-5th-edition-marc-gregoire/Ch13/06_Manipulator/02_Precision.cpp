/*
 * Chapter 13 - setprecision vs. precision()
 *
 * Most manipulators have an equivalent member-function form. This sample sets
 * the number of significant digits two ways: with the setprecision() inline
 * manipulator and with the precision() method.
 *
 * Key notes:
 *   - The method form returns the previous value, so you can save and restore
 *     it; the manipulator form does not.
 */

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	// Use setprecision manipulator.
	cout << "This should be '1.2346': " << setprecision(5) << 1.23456789 << endl;

	// Use precision() member function
	cout.precision(5);
	cout << "This should be '1.2346': " << 1.23456789 << endl;
}
