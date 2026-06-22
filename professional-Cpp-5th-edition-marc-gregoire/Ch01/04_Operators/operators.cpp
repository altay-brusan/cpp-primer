/*
 * Chapter 1 - Operators
 *
 * Common arithmetic, compound-assignment, and bitwise operators in one place. Two pitfalls
 * worth fixing in muscle memory: narrowing into a smaller integer type needs an explicit
 * static_cast, and "int / int" always performs integer division regardless of the type on
 * the left of the =. To get a real quotient, cast one operand to a floating-point type first.
 *
 * Key notes:
 *   - Pre vs post increment: ++i increments and yields the new value; i++ yields the old
 *     value and then increments. Prefer ++i for non-primitive types to avoid an extra copy.
 *   - Compound assignment: i += j is i = i + j; same pattern for -=, *=, /=, %=, &=, |=, ^=,
 *     <<=, >>=.
 *   - Modulo % only works on integral operands; for floating-point use std::fmod().
 *   - Bitwise operators: & AND, | OR, ^ XOR, ~ NOT, << left shift, >> right shift.
 *   - Precedence (high to low): postfix ++/--, prefix !/++/--, * / %, + -, << >>, &, ^, |,
 *     then assignment. When in doubt, add parentheses - readability beats remembering tables.
 *   - C++ uses short-circuit evaluation for && and ||: the right side is not evaluated once
 *     the result is decided. Useful for guarding pointers: "p && p->x".
 */

#include <print>

using namespace std;

int main()
{
	int someInteger{ 256 };
	short someShort;
	long someLong;
	float someFloat;
	double someDouble;

	someInteger++;
	someInteger *= 2;
	// Conversion from larger integer type to smaller integer type
	// can cause a warning or error, hence static_cast() is required.
	someShort = static_cast<short>(someInteger);
	someLong = someShort * 10000;
	someFloat = someLong + 0.785f;
	// To make sure the division is performed with double precision,
	// someFloat is explicitly converted to double first.
	someDouble = static_cast<double>(someFloat) / 100000;

	println("{}", someDouble);
}
