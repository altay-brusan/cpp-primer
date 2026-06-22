#pragma once

/*
 * Chapter 8 - Writing Classes / Calling Other Methods
 *
 * Same cell, now able to swallow text as well as numbers. The string entry path runs
 * through a private helper that parses the text into a double, and the read path runs
 * through another private helper that formats the double back to text. Internally the
 * cell still holds a single `double` - the string form is computed on demand.
 *
 * Key notes:
 *   - One member function can call another on the same object - that is what `setString()`
 *     does when it calls the private `stringToDouble()`.
 *   - Use `std::string_view` for read-only string parameters; copy into `std::string` only
 *     when you actually need to own the data.
 *   - Helpers that should not be part of the public API live in the private section.
 *   - Returning `std::string` by value is fine and idiomatic - handing back a `char*` to a
 *     local buffer would dangle.
 */

#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
	void setValue(double value);
	double getValue() const;

	void setString(std::string_view value);
	std::string getString() const;

private:
	std::string doubleToString(double value) const;
	double stringToDouble(std::string_view value) const;

	double m_value{ 0 };
};
