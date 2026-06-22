/*
 * Implementation for SpreadsheetCell.h - see the header for the conceptual notes.
 *
 * `setValue` names the receiver explicitly as `self`. All other member functions still use
 * the implicit-`this` form, so the two styles coexist.
 */

#include "SpreadsheetCell.h"
#include <charconv>
#include <print>

using namespace std;

void printCell(const SpreadsheetCell& cell)
{
	println("{}", cell.getString());
}

void SpreadsheetCell::setValue(this SpreadsheetCell& self, double value)
{
	self.m_value = value;   // `self` plays the role of `*this` from earlier folders
	printCell(self);        // pass the object straight through - no `*this` needed
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