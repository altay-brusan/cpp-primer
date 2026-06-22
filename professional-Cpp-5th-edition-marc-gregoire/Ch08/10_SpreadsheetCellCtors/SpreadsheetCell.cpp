/*
 * Implementation for SpreadsheetCell.h - see the header for the conceptual notes.
 *
 * Each constructor here delegates work to an existing setter. That is fine but slightly
 * wasteful - folder 14 rewrites the same constructors using a ctor-initializer, which is
 * the idiomatic form.
 */

#include "SpreadsheetCell.h"
#include <charconv>

using namespace std;

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
