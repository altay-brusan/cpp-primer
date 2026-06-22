/*
 * Chapter 13 - Input Basics: Reading an int
 *
 * The >> operator works with different variable types just like <<. Compared to
 * the string sample, only the variable's type changes: here cin reads directly
 * into an int.
 */

#include <iostream>
#include <print>

using namespace std;

int main()
{
	int userInput;
	cin >> userInput;
	println("User input was {}.", userInput);
}
