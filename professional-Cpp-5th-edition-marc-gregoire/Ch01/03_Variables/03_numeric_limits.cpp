/*
 * Chapter 1 - Numerical Limits
 *
 * std::numeric_limits<T>, defined in <limits>, is the type-safe C++ way to query the bounds
 * of a numeric type. It replaces the C-era macros like INT_MAX. Because it is a class template,
 * specify the type in angle brackets and call the static functions you need.
 *
 * Key notes:
 *   - For integer types, numeric_limits<T>::min() equals ::lowest() - both give the most
 *     negative representable value.
 *   - For floating-point types, ::min() returns the smallest POSITIVE value that can be
 *     represented; ::lowest() returns the most negative value (equals -max()). This trips
 *     people up - use ::lowest() when you want "the smallest possible float", not ::min().
 *   - Special floating-point values live in <cmath>: std::isnan(x) tests not-a-number,
 *     std::isinf(x) tests infinity. Get the constants via numeric_limits<double>::infinity()
 *     and numeric_limits<double>::quiet_NaN(), or use the macros INFINITY / NAN.
 *   - Use ::digits, ::digits10, ::is_signed, ::is_integer for compile-time queries.
 *
 * Example:
 *     float f = INFINITY;       std::isinf(f);   // true
 *     float n = NAN;            std::isnan(n);   // true
 *     auto big = std::numeric_limits<double>::max();
 *     auto neg = std::numeric_limits<double>::lowest();   // = -big
 */

#include <print>
#include <limits>

using namespace std;

int main()
{
	println("int:");
	println("Max int value: {}", numeric_limits<int>::max());
	println("Min int value: {}", numeric_limits<int>::min());
	println("Lowest int value: {}", numeric_limits<int>::lowest());
	
	println("\ndouble:");
	println("Max double value: {}", numeric_limits<double>::max());
	println("Min double value: {}", numeric_limits<double>::min());
	println("Lowest double value: {}", numeric_limits<double>::lowest());
}