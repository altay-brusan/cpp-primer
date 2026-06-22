/*
 * Chapter 9 - mutable Data Members
 *
 * Implementation for SpreadsheetCell.h - see the header for the conceptual notes.
 * The `const` accessors below increment `m_numAccesses` even though they are
 * const, which only compiles because the member is `mutable`.
 */
#include "SpreadsheetCell.h"
#include <charconv>

using namespace std;

SpreadsheetCell::SpreadsheetCell(double initialValue)
	: m_value { initialValue }
{
}

SpreadsheetCell::SpreadsheetCell(string_view initialValue)
	: m_value { stringToDouble(initialValue) }
{
}

void SpreadsheetCell::setValue(double value)
{
	m_value = value;
}

double SpreadsheetCell::getValue() const
{
	++m_numAccesses; // legal because m_numAccesses is declared `mutable`
	return m_value;
}

void SpreadsheetCell::setString(string_view value)
{
	m_value = stringToDouble(value);
}

string SpreadsheetCell::getString() const
{
	++m_numAccesses;
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
