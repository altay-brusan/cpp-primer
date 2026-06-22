/*
 * Chapter 13 - Span-Based Output Stream (ospanstream)
 *
 * The output counterpart: std::ospanstream (C++23) writes formatted data
 * directly into a caller-supplied fixed char buffer wrapped in a std::span, so
 * no dynamic allocation occurs. Here it formats a string, a double, and an int
 * into a 32-byte stack buffer.
 */

#include <print>
#include <span>
#include <spanstream>

using namespace std;

int main()
{
	char fixedBuffer[32]{};
	ospanstream stream{ span{ fixedBuffer } };
	stream << "Hello " << 2.222 << ' ' << 11;
	println("Buffer contents: \"{}\"", fixedBuffer);
}