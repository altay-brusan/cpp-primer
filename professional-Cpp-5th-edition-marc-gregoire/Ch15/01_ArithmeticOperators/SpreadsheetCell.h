/*
 * Chapter 15 - Overloading the Arithmetic Operators (SpreadsheetCell)
 *
 * Declares a SpreadsheetCell wrapping a single double, and the full set of arithmetic
 * operators discussed in this chapter. The binary +, -, *, / are global functions (so the
 * left-hand side may also be a plain double that converts via the constructor), while the
 * shorthand assignments +=, -=, *=, /= are members that do the actual work. Also shown:
 * unary operator-(), the prefix/postfix operator++ and operator--, and a defaulted
 * three-way operator<=> that yields all six comparison operators for free.
 *
 * Key notes:
 *   - Binary + - * and / are non-member functions that forward to the member += family.
 *   - operator++/operator-- distinguish prefix (no parameter, returns reference) from
 *     postfix (unused int parameter, returns the old value by value).
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
	SpreadsheetCell& operator++();   // Prefix
	SpreadsheetCell operator++(int); // Postfix
	SpreadsheetCell& operator--();   // Prefix 
	SpreadsheetCell operator--(int); // Postfix

private:
	double m_value{ 0 };
};

SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator-(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator*(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator/(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
