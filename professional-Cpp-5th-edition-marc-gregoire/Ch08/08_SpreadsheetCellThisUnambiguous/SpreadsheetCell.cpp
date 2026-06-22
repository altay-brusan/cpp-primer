/*
 * Implementation for SpreadsheetCell.h - see the header for the conceptual notes.
 *
 * `this->value` resolves the member-vs-parameter ambiguity, and `*this` passes the whole
 * object by reference into the free function `printCell()`.
 */

#include "SpreadsheetCell.h"
#include <charconv>
#include <print>

using namespace std;

void printCell(const SpreadsheetCell& cell)
{
	println("{}", cell.getString());
}

void SpreadsheetCell::setValue(double value)
{
	this->value = value;   // `this->` disambiguates member from parameter
	printCell(*this);      // `*this` is the cell itself - pass it by reference
}

double SpreadsheetCell::getValue() const
{
	return value;
}

void SpreadsheetCell::setString(string_view value)
{
	this->value = stringToDouble(value);
}

string SpreadsheetCell::getString() const
{
	return doubleToString(value);
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
