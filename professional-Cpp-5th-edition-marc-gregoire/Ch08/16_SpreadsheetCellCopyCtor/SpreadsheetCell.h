#pragma once

/*
 * Chapter 8 - Copy Constructors
 *
 * The copy constructor builds a new object as an exact copy of an existing one. Its
 * signature takes a reference-to-const of the same class:
 *     SpreadsheetCell(const SpreadsheetCell& src);
 * The compiler will write one for you that copies every member from `src`. You only need
 * to write your own when the default member-wise copy is not enough - the next chapter
 * shows when that happens, typically because of owned raw resources.
 *
 * Key notes:
 *   - Signature: `Class(const Class& src)`. Reference-to-const, no return type.
 *   - The copy constructor is one kind of constructor, so it must be used at initialization
 *     time, never later for an assignment.
 *   - Triggers: pass-by-value into a function, return-by-value from a function (subject to
 *     copy elision), and explicit copies like `T b { a };` or `T b = a;`.
 *   - The compiler-generated copy ctor calls each member's copy ctor in turn - perfect for
 *     classes that own only value-typed members like this one.
 *   - You can default it (`= default`) or forbid copying (`= delete`).
 *   - For performance, pass objects as `const Class&` to avoid invoking the copy ctor on
 *     every call.
 *
 * Example:
 *     // The hand-written copy ctor below could just as well be written:
 *     SpreadsheetCell(const SpreadsheetCell& src) = default;
 */

#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
	SpreadsheetCell() = default;
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(std::string_view initialValue);
	SpreadsheetCell(const SpreadsheetCell& src);

	void setValue(double value);
	double getValue() const;

	void setString(std::string_view value);
	std::string getString() const;

private:
	std::string doubleToString(double value) const;
	double stringToDouble(std::string_view value) const;

	double m_value{ 0 };
};
