/*
 * Chapter 13 - get(): Raw Character Input
 *
 * get() reads raw input one character at a time, bypassing the whitespace
 * tokenization of >>. readName() uses it to build a multi-word name until the
 * stream fails or end-of-file is reached. A more concise alternative version,
 * using the get(char&) overload that returns the stream, is kept in a
 * commented-out block at the bottom.
 *
 * Key notes:
 *   - The result of get() is stored in an int, not a char, because it can
 *     return special non-character values like char_traits<char>::eof().
 *   - The istream parameter is reference-to-non-const: reading mutates the
 *     stream (its position), so those methods are non-const.
 */

#include <iostream>
#include <print>
#include <string>

using namespace std;

string readName(istream& stream);

int main()
{
	println("Type a name followed by Enter followed by Control+D (Control+Z in Windows) and another Enter: ");
	string theName{ readName(cin) };

	println("The name is \"{}\".", theName);
}


string readName(istream& stream)
{
	string name;
	while (stream) { // Or: while (!stream.fail()) {
		int next{ stream.get() };
		if (!stream || next == std::char_traits<char>::eof())
			break;
		name += static_cast<char>(next);// Append character.
	}
	return name;
}


/*
string readName(istream& stream)
{
	string name;
	char next;
	while (stream.get(next)) {
		name += next;
	}

	return name;
}
*/