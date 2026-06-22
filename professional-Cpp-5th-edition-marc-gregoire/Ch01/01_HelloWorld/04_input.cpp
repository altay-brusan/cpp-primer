/*
 * Chapter 1 - I/O Streams (input side)
 *
 * std::cin is the standard input stream; operator>> extracts a value from it into the target
 * variable, attempting to parse the text the user typed. User input is inherently messy - you
 * cannot trust what the user will type - and Chapter 13 covers robust input handling.
 *
 * Key notes:
 *   - std::cin >> x parses according to x's type; if the parse fails, cin enters a fail state
 *     and subsequent reads do nothing until you clear() and ignore() the bad input.
 *   - operator>> skips leading whitespace by default and stops at the next whitespace.
 *   - To read a full line including spaces, use std::getline(std::cin, str).
 */

#include <iostream>
#include <print>

int main()
{
	int value;
	std::cin >> value;
	std::println("You entered {}", value);

	return 0;
}
