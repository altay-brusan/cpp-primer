/*
 * Chapter 2 - High-Level Numeric Conversions: Converting to Strings
 *
 * std::to_string() (declared in <string>) is the simple, high-level way to turn a number
 * into an std::string. There are overloads for (unsigned) int, (unsigned) long, (unsigned)
 * long long, float, double, and long double. Each call constructs and returns a brand-new
 * std::string and handles allocation internally - convenient, but with no knobs to tune.
 *
 * Key notes:
 *   - Output is always base-10. There is no way to pick hex/oct/binary via to_string();
 *     reach for std::format("{:x}", value) or std::to_chars() when you need that.
 *   - Floating-point output uses the default precision (typically 6 digits), so 3.14L
 *     formats as "3.140000". This means to_string() does NOT guarantee a perfect
 *     round-trip back to the same floating-point value.
 *   - For locale-independent, high-performance, round-trip-safe conversion, prefer
 *     std::to_chars() from <charconv>.
 */

#include <print>
#include <string>

using namespace std;

int main()
{
	long double d{ 3.14L };
	string s{ to_string(d) };  // s contains 3.140000
	println("{}", s);
}