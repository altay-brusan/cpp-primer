/*
 * Chapter 24 - Decomposing tuples with structured bindings
 *
 * Demonstrates structured bindings (C++17), one of the two ways to decompose a
 * tuple into individual named variables. A "auto [i, str, b]" binding copies the
 * elements out, while a "auto and [i2, str2, b2]" binding binds references, so
 * assigning through them modifies the original tuple. Structured bindings require
 * exactly one name per element and cannot skip elements; use std::tie() (see
 * 04_tuple_tie.cpp) when you need to ignore some.
 */

#include <print>
#include <tuple>
#include <string>

using namespace std;

int main()
{
	tuple t1{ 16, "Test"s, true };   // Using CTAD
	// Or:
	//tuple<int, string, bool> t1{ 16, "Test", true };

	auto [i, str, b] { t1 };
	println("Decomposed: i = {}, str = \"{}\", b = {}", i, str, b);

	println("Before: {}", t1);

	auto& [i2, str2, b2] { t1 };
	i2 *= 2;
	str2 = "Hello World";
	b2 = !b2;

	println("After: {}", t1);
}