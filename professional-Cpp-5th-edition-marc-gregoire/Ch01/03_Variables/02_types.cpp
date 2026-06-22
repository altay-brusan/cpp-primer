/*
 * Chapter 1 - Variables (built-in types tour)
 *
 * A walk through the fundamental C++ types: signed/unsigned integer widths
 * (short, int, long, long long), floating-point types (float, double, long double),
 * the character family (char, char8_t/16_t/32_t for UTF-encoded code units, wchar_t),
 * bool, and std::byte from <cstddef> for "this is raw memory, not a character".
 *
 * Key notes:
 *   - char is a distinct type from both signed char and unsigned char. It may be signed or
 *     unsigned depending on the compiler; do not rely on its signedness. Use char only for
 *     characters.
 *   - Use std::byte (since C++17, in <cstddef>) when you mean a byte of memory. Initialize
 *     with: std::byte b { 42 };
 *   - Integer sizes are not fixed by the standard - only minimums. Typical sizes: short >= 2,
 *     int >= 2 (usually 4), long >= 4, long long >= 8 bytes. For fixed widths use the
 *     int8_t / int16_t / int32_t / int64_t aliases from <cstdint>.
 *   - Literal suffixes: 7L (long), 14LL (long long), 2U (unsigned), 5UL, 140ULL, 7.2f (float),
 *     7.2 (double), 16.98L (long double).
 *   - Character literal prefixes: 'm' (char), u8'm' (char8_t), u'm' (char16_t),
 *     U'm' (char32_t), L'm' (wchar_t).
 *   - Digit separators: 1'000'000 is the same as 1000000 - just a readability aid.
 *   - bool has exactly two values, true and false. Any non-zero value converts to true.
 */

#include <cstddef>

int main()
{
	int i1{ -7 };
	signed int i2{ -6 };
	signed i3{ -5 };

	short s1{ 13 };
	short int s2{ 14 };
	signed short s3{ 15 };
	signed short int s4{ 16 };

	long l{ -7L };

	long long ll{ 14LL };

	unsigned int ui{ 2U };
	unsigned uj{ 5U };
	unsigned short us{ 23U };
	unsigned long ul{ 5400UL };
	unsigned long long ull{ 140ULL };

	float f{ 7.2f };

	double d{ 7.2 };

	long double ld{ 16.98L };

	char ch{ 'm' };

	char8_t c8{ u8'm' };
	char16_t c16{ u'm' };
	char32_t c32{ U'm' };

	wchar_t w{ L'm' };

	bool b1{ true };

	std::byte b2{ 42 };
}
