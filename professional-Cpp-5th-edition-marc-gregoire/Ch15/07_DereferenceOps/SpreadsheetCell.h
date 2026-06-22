/*
 * Chapter 15 - Supporting SpreadsheetCell (pointee type for the Pointer demo)
 *
 * The arithmetic-operator version of SpreadsheetCell, reused here only as the object type
 * that the Pointer smart-pointer template points to. It provides the arithmetic, increment/
 * decrement, and defaulted operator<=> declarations; the dereferencing operators that are
 * the focus of this folder live in Pointer.h.
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

private:
	double m_value{ 0 };
};

SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator-(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator*(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator/(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
