/*
 * Chapter 1 - Casting
 *
 * Three syntaxes for an explicit type change: the C-style cast (int)x, the function-style
 * int(x), and the verbose but recommended static_cast<int>(x). Prefer static_cast - it is
 * searchable, checked at compile time, and refuses unrelated conversions. C-style casts hide
 * intent and can quietly become a reinterpret_cast or const_cast.
 *
 * Key notes:
 *   - float -> int truncates the fractional part. If the float exceeds INT_MAX/INT_MIN the
 *     result is undefined behavior.
 *   - Widening conversions (short -> long, int -> double) happen implicitly; no cast needed.
 *   - Narrowing assignments compile but warn; under uniform initialization "int x { 3.14 };"
 *     they are a hard error - one of the reasons to prefer braces.
 *   - C++ has five named casts: static_cast, const_cast, reinterpret_cast, dynamic_cast, and
 *     std::bit_cast (C++20). Only const_cast can strip const-ness.
 *   - For deliberately narrowing casts where you accept the loss, consider gsl::narrow_cast()
 *     from the Guidelines Support Library.
 */

int main()
{
	float myFloat{ 3.14f };
	int i1{ (int)myFloat };                // method 1
	int i2{ int(myFloat) };                // method 2
	int i3{ static_cast<int>(myFloat) };   // method 3

	short someShort{ 16 };
	long someLong{ someShort };          // no explicit cast needed
}