/*
 * Chapter 22 - Compile-Time Rational Numbers with <ratio>
 *
 * Demonstrates std::ratio, a class template that exactly represents a finite
 * rational number entirely at compile time. The numerator and denominator are
 * stored as static intmax_t constants (::num and ::den), automatically reduced
 * to lowest terms. The <ratio> library underpins the chrono durations, where a
 * ratio describes the length of one tick relative to a second.
 *
 * Key notes:
 *   - Arithmetic helpers like ratio_add produce a new ratio type accessible via
 *     ::type; comparison helpers like ratio_less expose a bool ::value.
 *   - Because everything is a type computed by the compiler, there is no runtime
 *     cost and no rounding error.
 */

#include <print>
#include <ratio>
#include <cstdint>

using namespace std;

int main()
{
	// Define a compile-time rational number.
	using r1 = ratio<1, 60>;

	// Get numerator and denominator.
	intmax_t num{ r1::num };
	intmax_t den{ r1::den };
	println("1) r1 = {}/{}", num, den);

	// Add two rational numbers.
	using r2 = ratio<1, 30>;
	println("2) r2 = {}/{}", r2::num, r2::den);
	using result = ratio_add<r1, r2>::type;
	println("3) sum = {}/{}", result::num, result::den);

	// Compare two rational numbers.
	using res = ratio_less<r2, r1>;
	println("4) r2 < r1: {}", res::value);
}
