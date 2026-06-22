/*
 * Chapter 9 - Pre-C++20 Comparison Operators
 *
 * Before C++20 there was no spaceship; comparing two cells required SIX free
 * functions: `operator==`, `!=`, `<`, `>`, `<=`, `>=`. They are written as
 * free functions for the same reason the arithmetic operators are: implicit
 * conversions then work on either side of the operator.
 *
 * Key notes:
 *   - Each operator returns `bool`. Changing the return type is legal but
 *     misleading.
 *   - Once you have `==` and `<`, the other four can be implemented in terms of
 *     them - but that is still six functions per class.
 *   - To compare a SpreadsheetCell with a `double` without creating a temporary,
 *     you would add 12 more functions (three overloads x six operators). C++20
 *     reduces this to a single `<=>` overload (folder 5).
 *   - Equality on floating-point values is fraught; an epsilon comparison is the
 *     usual recommendation in real code.
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
bool operator==(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
bool operator<(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
bool operator>(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
bool operator!=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
bool operator<=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
bool operator>=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
