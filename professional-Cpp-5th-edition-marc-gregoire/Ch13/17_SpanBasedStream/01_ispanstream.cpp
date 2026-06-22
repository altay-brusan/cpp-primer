/*
 * Chapter 13 - Span-Based Input Stream (ispanstream)
 *
 * std::ispanstream (C++23, <spanstream>) gives stream semantics over an
 * existing, fixed character buffer via a std::span, without copying it into a
 * string. Here it parses an int, a double, and a string out of a stack buffer
 * with the usual >> operator.
 */

#include <print>
#include <span>
#include <spanstream>
#include <string>

using namespace std;

int main()
{
	char fixedBuffer[]{ "11 2.222 Hello" };

	ispanstream stream{ span{ fixedBuffer } };

	int i;
	double d;
	string str;
	stream >> i >> d >> str;

	println("Parsed data: int: {}, double: {}, string: {}", i, d, str);
}