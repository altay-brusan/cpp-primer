/*
 * Chapter 9 - Operator Overloading: Global Arithmetic Operators
 *
 * Free-function operators take both operands as parameters, so implicit conversion
 * is allowed to fire on either side. `5.6 + myCell` and `myCell + 5.6` both work
 * because either operand can be converted to a SpreadsheetCell. The shorthand
 * operators (`+=`, `-=`, ...) stay as member functions, since the left operand is
 * always the object being modified.
 *
 * Key notes:
 *   - Implement the in-place operators (`operator+=`, etc.) as members; they have
 *     a guaranteed left-hand SpreadsheetCell and return `*this` by reference.
 *   - Implement the binary arithmetic operators (`operator+`, etc.) as free
 *     functions, ideally in terms of the member shorthand versions to avoid
 *     duplication:
 *         auto result{ lhs }; result += rhs; return result;
 *   - Free-function operators do NOT have to be friends if all the data they need
 *     is reachable through public accessors (here, `getValue()`).
 *   - `operator/` throws on divide-by-zero - perfectly legal, and a good place to
 *     surface bad input.
 *   - You cannot change operator precedence, arity, or invent new symbols. You
 *     can only swap in your own implementation for the existing operators.
 *
 * Example:
 *     // Implement operator+ in terms of operator+= to avoid two copies of the
 *     // logic:
 *     SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
 *     { auto result{ lhs }; result += rhs; return result; }
 */
#pragma once

#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
	SpreadsheetCell() = default;
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(std::string_view initialValue);

	void set(double value);
	void set(std::string_view value);

	double getValue() const;
	std::string getString() const;

	SpreadsheetCell& operator+=(const SpreadsheetCell& rhs);
	SpreadsheetCell& operator-=(const SpreadsheetCell& rhs);
	SpreadsheetCell& operator*=(const SpreadsheetCell& rhs);
	SpreadsheetCell& operator/=(const SpreadsheetCell& rhs);

private:
	static std::string doubleToString(double value);
	static double stringToDouble(std::string_view value);

	double m_value{ 0 };
};

SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator-(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator*(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator/(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
