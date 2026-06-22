/*
 * Implementation for SpreadsheetCell.h - see the header for the conceptual notes.
 *
 * The self-assignment check uses pointer equality - `this` for the left-hand side,
 * `&rhs` for the right-hand side. The unconditional `return *this;` at the end is what
 * makes `a = b = c;` work.
 */

#include "SpreadsheetCell.h"
#include <charconv>

using namespace std;

SpreadsheetCell::SpreadsheetCell(double initialValue)
	: m_value{ initialValue }
{
}

SpreadsheetCell::SpreadsheetCell(string_view initialValue)
	: m_value{ stringToDouble(initialValue) }
{
}

SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell& src)
	: m_value{ src.m_value }
{
}

SpreadsheetCell& SpreadsheetCell::operator=(const SpreadsheetCell& rhs)
{
	if (this == &rhs) {       // self-assignment guard
		return *this;
	}
	m_value = rhs.m_value;    // member-wise copy from rhs
	return *this;             // return the assigned-to object by reference, enables chaining
}

void SpreadsheetCell::setValue(double value)
{
	m_value = value;
}

double SpreadsheetCell::getValue() const
{
	return m_value;
}

void SpreadsheetCell::setString(string_view value)
{
	m_value = stringToDouble(value);
}

string SpreadsheetCell::getString() const
{
	return doubleToString(m_value);
}

string SpreadsheetCell::doubleToString(double value) const
{
	return to_string(value);
}

double SpreadsheetCell::stringToDouble(string_view value) const
{
	double number{ 0 };
	from_chars(value.data(), value.data() + value.size(), number);
	return number;
}
