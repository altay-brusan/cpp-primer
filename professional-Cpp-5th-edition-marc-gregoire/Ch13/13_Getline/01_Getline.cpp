/*
 * Chapter 13 - getline(): Reading a Whole Line
 *
 * Two ways to read a full line, including embedded whitespace, up to the
 * end-of-line. The cin.getline() method fills a fixed char buffer (size
 * includes the terminating \0). The free function std::getline() (from
 * <string>) reads into a std::string and needs no buffer-size argument.
 *
 * Key notes:
 *   - In both forms the end-of-line sequence is consumed but does not appear in
 *     the result; the exact sequence (\n, \r\n, ...) is platform dependent.
 */

#include <iostream>
#include <print>
#include <string>

using namespace std;

const size_t BufferSize{ 1024 };

int main()
{
	println("Enter a line of text:");
	char buffer[BufferSize]{ 0 };
	cin.getline(buffer, BufferSize);
	println("\"{}\"", buffer);

	println("");

	println("Enter another line of text:");
	string myString;
	getline(cin, myString);
	println("\"{}\"", myString);
}
