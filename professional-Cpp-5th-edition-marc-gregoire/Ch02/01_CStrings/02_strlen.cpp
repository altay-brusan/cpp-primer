/*
 * Chapter 2 - C-Style Strings: sizeof versus strlen
 *
 * sizeof() and strlen() are not interchangeable on C-style strings. sizeof() is evaluated
 * at compile time and reports the storage size of its operand; strlen() walks the bytes at
 * run time and counts characters up to (but not including) the '\0' terminator. For a
 * char[] initialized from a literal, sizeof() returns the array length, which equals the
 * number of characters plus 1 for the NUL. For a const char*, sizeof() collapses to the
 * size of a pointer on the current platform and tells you nothing about the string.
 *
 * Key notes:
 *   - char text1[] { "abcdef" };  // sizeof(text1) == 7, strlen(text1) == 6.
 *   - const char* text2 { "abcdef" };  // sizeof(text2) is 4 on x86, 8 on x64 - pointer size.
 *   - Rule of thumb: use strlen() for the character count, sizeof() only for raw storage.
 *   - Decaying a char[] to a char* (e.g., by passing it to a function) loses the array size.
 *   - sizeof(char) is always 1 by definition, regardless of platform.
 */

#include <print>
#include <cstring>

using namespace std;

int main()
{
	char text1[]{ "abcdef" };
	size_t s1{ sizeof(text1) };  // is 7
	size_t s2{ strlen(text1) };  // is 6
	println("{}\n{}", s1, s2);

	const char* text2{ "abcdef" };
	size_t s3{ sizeof(text2) };  // is platform-dependent (e.g. 4 bytes for x86, 8 bytes for x64)
	size_t s4{ strlen(text2) };  // is 6
	println("{}\n{}", s3, s4);
}
