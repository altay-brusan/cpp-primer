/*
 * Chapter 13 - putback(): Replacing a Character
 *
 * putback() also moves back one character in an input stream, but unlike
 * unget() it takes the character to place back as a parameter. That character
 * becomes the next one read off the stream.
 */

#include <iostream>
#include <print>

using namespace std;

int main()
{
	char c;
	cin >> c;
	println("Retrieved {}.", c);

	cin.putback('e');  // 'e' will be the next character read off the stream.
	println("Called putback('e').");
	
	while (cin >> c) {
		println("Retrieved {}.", c);
	}
}
