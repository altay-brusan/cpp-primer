/*
 * Implementation for SpreadsheetCell.h - see the header for the conceptual notes.
 *
 * The default constructor body is empty - the in-class initializer on `m_value` already
 * sets the field to 0. Folder 13 shows the cleaner `= default` shorthand for cases like
 * this.
 */

#include "SpreadsheetCell.h"
#include <charconv>

using namespace std;

SpreadsheetCell::SpreadsheetCell()
{
}

SpreadsheetCell::SpreadsheetCell(double initialValue)
{
	setValue(initialValue);
}

SpreadsheetCell::SpreadsheetCell(string_view initialValue)
{
	setString(initialValue);
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
