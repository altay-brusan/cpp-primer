/*
 * Chapter 15 - Writing Conversion Operators
 *
 * Adds conversion operators to SpreadsheetCell: operator double() and
 * operator std::string(). These let a SpreadsheetCell be used wherever a double or a
 * string is expected (double d{ cell };). A conversion operator has no return type in its
 * declaration - the type is part of the name - and is marked const because it does not
 * modify the object.
 *
 * Key notes:
 *   - Because string has matching constructors, uniform-initialization "string s{ cell }"
 *     is ambiguous; use "string s = cell;" or static_cast<string>(cell) instead.
 */
#pragma once

#include <string>
#include <string_view>
#include <compare>

class SpreadsheetCell
{
public:
	SpreadsheetCell() = default;
	SpreadsheetCell(double initialValue);
	explicit SpreadsheetCell(std::string_view initialValue);

	void set(double value);
	void set(std::string_view value);

	inline double getValue() const { return m_value; }
	inline std::string getString() const { return doubleToString(m_value); }

	static std::string doubleToString(double value);
	static double stringToDouble(std::string_view value);

	SpreadsheetCell& operator+=(const SpreadsheetCell& rhs);
	SpreadsheetCell& operator-=(const SpreadsheetCell& rhs);
	SpreadsheetCell& operator*=(const SpreadsheetCell& rhs);
	SpreadsheetCell& operator/=(const SpreadsheetCell& rhs);
	
	[[nodiscard]] auto operator<=>(const SpreadsheetCell&) const = default;
	
	SpreadsheetCell operator-() const;
	SpreadsheetCell& operator++();   // prefix
	SpreadsheetCell operator++(int); // postfix
	SpreadsheetCell& operator--();   // prefix 
	SpreadsheetCell operator--(int); // postfix

	operator double() const;
	operator std::string() const;

private:
	double m_value{ 0 };
};

SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator-(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator*(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator/(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
