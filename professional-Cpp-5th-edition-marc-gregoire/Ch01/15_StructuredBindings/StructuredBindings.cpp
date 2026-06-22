/*
 * Chapter 1 - Structured Bindings
 *
 * Structured bindings (C++17) declare several variables in one statement, each initialized
 * from a piece of an array, std::pair, std::tuple, or struct on the right-hand side. They
 * make decomposing aggregates one-liner clean.
 *
 * Key notes:
 *   - Always introduced with auto; you cannot spell out the element types (no "int [a, b]").
 *   - The count of names on the left must match the count of elements on the right.
 *   - Struct decomposition requires all non-static data members to be public. Members are
 *     bound in declaration order, regardless of the names you choose.
 *   - Bind by reference with "auto& [a, b] = obj;" to avoid copies and to modify the
 *     originals. "const auto& [a, b] = obj;" gives references-to-const.
 *   - Works in range-based for: "for (auto& [k, v] : map) { ... }".
 *
 * Example:
 *     std::pair p { "hello", 5 };
 *     auto& [name, score] { p };   // name and score are references into p
 */

#include <print>
#include <array>
#include <utility>

using namespace std;

int main()
{
	{
		// Structured bindings with std::array.
		array values{ 11, 22, 33 };
		auto [x, y, z] { values };
	}

	{
		// Structured bindings with struct.
		struct Point { double m_x, m_y, m_z; };
		Point point;
		point.m_x = 1.0; point.m_y = 2.0; point.m_z = 3.0;
		auto [x, y, z] { point };
	}

	{
		// Structured bindings with std::pair.
		pair myPair{ "hello", 5 };
		auto [theString, theInt] { myPair };  // Decompose using structured bindings
		println("theString: {}", theString);
		println("theInt: {}", theInt);
	}
}
