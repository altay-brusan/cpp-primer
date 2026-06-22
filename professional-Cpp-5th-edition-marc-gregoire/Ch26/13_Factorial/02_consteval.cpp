/*
 * Chapter 26 - consteval Instead of Template Recursion
 *
 * Computes the same factorial without any templates by using a C++20 consteval
 * immediate function. A consteval function is guaranteed to run at compile time,
 * making it a simpler alternative to recursive template metaprogramming for
 * plain compile-time computations.
 */

#include <print>

using namespace std;

consteval unsigned long long factorial(int f)
{
	if (f == 0) {
		return 1;
	} else {
		return f * factorial(f - 1);
	}
}

int main()
{
	println("{}", factorial(6));
}
