/*
 * Chapter 15 - Overloading the Insertion and Extraction Operators (SpreadsheetCell)
 *
 * Extends the arithmetic SpreadsheetCell with the I/O stream operators operator<< and
 * operator>>. Because the left-hand operand of these operators is a stream (ostream /
 * istream), not a SpreadsheetCell, they must be global functions rather than members.
 * Each takes a reference to the stream as its first parameter and returns that same stream
 * reference so that calls can be chained (cin >> a >> b; cout << a << b;).
 *
 * Key notes:
 *   - operator<< takes the cell by reference-to-const (it only reads it); operator>> takes
 *     it by reference-to-non-const because extraction modifies the cell.
 */
#pragma once

#include <string>
#include <string_view>
#include <compare>
#include <iostream>

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

private:
	double m_value{ 0 };
};

SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator-(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator*(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator/(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
std::ostream& operator<<(std::ostream& ostr, const SpreadsheetCell& cell);
std::istream& operator>>(std::istream& istr, SpreadsheetCell& cell);
