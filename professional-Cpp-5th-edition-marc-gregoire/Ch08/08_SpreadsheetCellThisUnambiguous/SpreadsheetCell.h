#pragma once

/*
 * Chapter 8 - The this Pointer (unambiguous version)
 *
 * Every non-static member function quietly receives a hidden first argument named `this`,
 * which points at the object the function is running on. Inside the function, `this->name`
 * unambiguously refers to a member, even when a parameter shadows it. Dereferencing
 * (`*this`) gives you the object itself, useful for passing it to free functions that
 * accept a `SpreadsheetCell&`.
 *
 * Key notes:
 *   - `this` is a pointer, so use `this->member` to reach a member.
 *   - `*this` is the object; pass `*this` when a function wants a reference to the cell.
 *   - With an `m_` prefix on members you rarely need to write `this->` at all, but it is
 *     always available as an explicit disambiguator.
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

	double value{ 0 };
};
