/*
 * Chapter 13 - getline() with a Custom Delimiter
 *
 * std::getline() accepts an optional delimiter as its last argument (default
 * '\n'). By passing '@' here, it keeps reading across multiple lines until the
 * '@' character is encountered, letting you capture a whole multi-line block in
 * one call.
 */

#include <iostream>
#include <print>
#include <string>

using namespace std;

int main()
{
	print("Enter multiple lines of text. "
		"Use an @ character to signal the end of the text.\n> ");

	string myString;
	getline(cin, myString, '@');

	println("Read text: \"{}\"", myString);
}
