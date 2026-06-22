/*
 * Implementation for SpreadsheetCell.h - see the header for the conceptual notes.
 *
 * The string_view constructor parses its argument once and delegates the rest of the
 * construction to the double-arg constructor. Note that the delegation expression takes
 * the place of the `m_value { ... }` entry - both cannot coexist in the same initializer
 * list.
 */

#include "SpreadsheetCell.h"
#include <charconv>

using namespace std;

SpreadsheetCell::SpreadsheetCell(double initialValue)
	: m_value{ initialValue }
{
}

SpreadsheetCell::SpreadsheetCell(string_view initialValue)
	: SpreadsheetCell{ stringToDouble(initialValue) }
{
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
