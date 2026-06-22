/*
 * Chapter 1 - I/O Streams
 *
 * Two classic ways to produce formatted output: chain values into std::cout with the <<
 * operator, or build the string with std::format() (C++20) and stream that. Think of an
 * output stream as a chute - operator<< tosses items down the chute in order. std::cerr is
 * a separate chute that targets the error console.
 *
 * Key notes:
 *   - std::endl inserts '\n' AND flushes the stream's buffers. Overusing endl in a loop is
 *     a performance hit; use '\n' when you do not need an immediate flush.
 *   - Escape sequences in string literals: \n newline, \r carriage return, \t tab, \\ backslash,
 *     \" double quote.
 *   - std::format() returns a std::string; std::cout << std::format(...) then writes it.
 *   - Streams accept many types in sequence: cout << "x = " << 219 << " items\n";
 *
 * Example:
 *     std::cout << "tight loop\n";   // prefer over endl inside loops
 */

#include <iostream>
#include <format>

int main()
{
	std::cout << "There are " << 219 << " ways I love you." << std::endl;

	std::cout << std::format("There are {} ways I love you.", 219) << std::endl;

	return 0;
}
