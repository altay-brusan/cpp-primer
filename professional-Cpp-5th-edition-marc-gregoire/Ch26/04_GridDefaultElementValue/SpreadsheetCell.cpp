/*
 * Chapter 26 - Implementation for SpreadsheetCell.h - see the header for the conceptual notes.
 *
 * Provides a small helper value class used by the non-type template parameter
 * example to demonstrate which types may not be used as non-type arguments.
 */

#include "SpreadsheetCell.h"
#include <charconv>
#include <stdexcept>

using namespace std;

SpreadsheetCell::SpreadsheetCell(double initialValue)
	: m_value { initialValue }
{
}

SpreadsheetCell::SpreadsheetCell(string_view initialValue)
	: m_value { stringToDouble(initialValue) }
{
}

void SpreadsheetCell::set(double value)
{
	m_value = value;
}

double SpreadsheetCell::getValue() const
{
	return m_value;
}

void SpreadsheetCell::set(string_view value)
{
	m_value = stringToDouble(value);
}

string SpreadsheetCell::getString() const
{
	return doubleToString(m_value);
}

string SpreadsheetCell::doubleToString(double value)
{
	return to_string(value);
}

double SpreadsheetCell::stringToDouble(string_view value)
{
	double number{ 0 };
	from_chars(value.data(), value.data() + value.size(), number);
	return number;
}

SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
	auto result{ lhs };  // Local copy
	result += rhs;       // Forward to +=()
	return result;
}

SpreadsheetCell operator-(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
	auto result{ lhs };  // Local copy
	result -= rhs;       // Forward to -=()
	return result;
}

SpreadsheetCell operator*(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
	auto result{ lhs };  // Local copy
	result *= rhs;       // Forward to *=()
	return result;
}

SpreadsheetCell operator/(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
	auto result{ lhs };  // Local copy
	result /= rhs;       // Forward to /=()
	return result;
}

SpreadsheetCell& SpreadsheetCell::operator+=(const SpreadsheetCell& rhs)
{
	set(getValue() + rhs.getValue());
	return *this;
}

SpreadsheetCell& SpreadsheetCell::operator-=(const SpreadsheetCell& rhs)
{
	set(getValue() - rhs.getValue());
	return *this;
}

SpreadsheetCell& SpreadsheetCell::operator*=(const SpreadsheetCell& rhs)
{
	set(getValue() * rhs.getValue());
	return *this;
}

SpreadsheetCell& SpreadsheetCell::operator/=(const SpreadsheetCell& rhs)
{
	if (rhs.getValue() == 0) {
		throw invalid_argument { "Divide by zero." };
	}
	set(getValue() / rhs.getValue());
	return *this;
}
