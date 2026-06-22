/*
 * Chapter 26 - Template Metaprogramming: Factorial at Compile Time
 *
 * Computes a factorial entirely at compile time using template recursion. The
 * primary Factorial<f> defines a static constant value in terms of
 * Factorial<f-1>::value, and the full specialization Factorial<0> provides the
 * base case value of 1. At run time only the precomputed constant is read.
 *
 * Key notes:
 *   - This pairs a recursive template with a base (specialized) template, the
 *     classic metaprogramming pattern.
 */

#include <print>

using namespace std;

template <int f>
class Factorial
{
public:
	static constexpr unsigned long long value{ f * Factorial<f - 1>::value };
};

template <>
class Factorial<0>
{
public:
	static constexpr unsigned long long value{ 1 };
};

int main()
{
	println("{}", Factorial<6>::value);
}
