/*
 * Chapter 15 - Reading and Writing Objects with Stream Operators
 *
 * Driver demonstrating the overloaded I/O stream operators. It reads three
 * SpreadsheetCells from cin with chained operator>> and writes them back with chained
 * operator<<. The final line spells out the chaining explicitly as nested
 * operator>>(operator>>(...)) calls to show that the operator syntax is just shorthand.
 *
 * Key notes:
 *   - Interactive: this program blocks waiting for keyboard input on cin, so it does not
 *     run unattended (feed it numbers/strings on stdin).
 */
#include "SpreadsheetCell.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	int number{ 10 };
	cout << "The number is " << number << endl;
	
	cout << "Enter a number and a string: ";
	string str;
	cin >> number >> str;
	cout << "You entered: " << number << " and " << str << endl;

	SpreadsheetCell myCell, anotherCell, aThirdCell;

	cout << "Input 3 spreadsheetcells:" << endl;
	cin >> myCell >> anotherCell >> aThirdCell;
	cout << myCell << " " << anotherCell << " " << aThirdCell << endl;

	cout << "Input 3 spreadsheetcells:" << endl;
	operator>>(operator>>(operator>>(cin, myCell), anotherCell), aThirdCell);
}
