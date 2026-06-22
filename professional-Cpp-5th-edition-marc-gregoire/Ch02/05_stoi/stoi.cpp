/*
 * Chapter 2 - High-Level Numeric Conversions: Converting from Strings
 *
 * std::stoi() parses an int out of a leading run of digits in an std::string. The full
 * family covers every common numeric type: stol, stoul, stoll, stoull for integers and
 * stof, stod, stold for floating-point. All of them ignore leading whitespace, then read
 * as far as they can. The optional idx out-parameter is set to the index of the first
 * character that was NOT consumed, which here is the 'U' of "USD" after parsing 123.
 *
 * Key notes:
 *   - Signature: int stoi(const string& str, size_t* idx = nullptr, int base = 10);
 *   - Integer overloads accept a base; base = 0 enables auto-detection: a leading 0x/0X
 *     means hex, a leading 0 means octal, otherwise decimal.
 *   - Throws std::invalid_argument when no conversion could be made (e.g., stoi("abc")).
 *   - Throws std::out_of_range when the parsed value does not fit the return type.
 *   - The idx tells you where parsing stopped; that index can equal str.size() if every
 *     character was consumed.
 *   - For locale-independent, non-throwing, allocation-free parsing, prefer
 *     std::from_chars() from <charconv>.
 */

#include <print>
#include <string>
#include <cstddef>

using namespace std;

int main()
{
	const string toParse{ "   123USD" };
	size_t index{ 0 };
	int value{ stoi(toParse, &index) };
	println("Parsed value: {}", value);
	println("First non-parsed character: '{}'", toParse[index]);
}