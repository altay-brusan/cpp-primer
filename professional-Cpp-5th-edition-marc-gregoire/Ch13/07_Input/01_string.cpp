/*
 * Chapter 13 - Input Basics: Reading a String
 *
 * The >> operator is the input counterpart of <<: the variable you provide is
 * the storage for the value read from cin. This reads one word into a string.
 *
 * Key notes:
 *   - >> tokenizes on whitespace, so entering "hello there" stores only
 *     "hello". To capture whitespace, use get() or getline() (later samples).
 */

#include <iostream>
#include <print>
#include <string>

using namespace std;

int main()
{
	string userInput;
	cin >> userInput;
	println("User input was {}.", userInput);
}
