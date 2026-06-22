/*
 * Implementation for SpreadsheetCell.h - see the header for the conceptual notes.
 *
 * Same copy constructor and assignment operator as folder 23. The driver in this folder
 * walks through the subtle difference between the two.
 */

#include "SpreadsheetCell.h"
#include <charconv>
#include <iostream>

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
	std::cout<<"Copy constructor called for value: " << m_value << std::endl;
}

SpreadsheetCell& SpreadsheetCell::operator=(const SpreadsheetCell& rhs)
{
	if (this == &rhs) {
		return *this;
	}
	m_value = rhs.m_value;
	std::cout<<"Assignment operator called for value: " << m_value << std::endl;
	return *this;
}

void SpreadsheetCell::setValue(double value)
{
	m_value = value;
	std::cout<<"setValue called for value: " << m_value << std::endl;	
}

double SpreadsheetCell::getValue() const
{
	return m_value;
}

void SpreadsheetCell::setString(string_view value)
{
	m_value = stringToDouble(value);
	std::cout<<"setString called for value: " << m_value << std::endl;
}

string SpreadsheetCell::getString() const
{
	std::cout<<"getString called for value: " << m_value << std::endl;
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
