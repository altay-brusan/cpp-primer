#pragma once

/*
 * Chapter 8 - The this Pointer (ambiguous version)
 *
 * The data member here is named `value` instead of `m_value`, and the setter parameter is
 * also named `value`. In `setValue(double value)` the parameter shadows the member, so
 * `value = value;` is a parameter-to-parameter self-assignment - a no-op rather than the
 * write you wanted. The folder name `ThisAmbiguous` is the warning label: this is what
 * you do not want to do. Folder 08 fixes it with the `this` pointer; the naming convention
 * fix (the `m_` prefix used elsewhere in the chapter) prevents the collision entirely.
 *
 * Key notes:
 *   - Adopting an `m_` prefix on data members sidesteps shadowing of parameters by
 *     members.
 *   - The line `value = value;` compiles cleanly on most compilers, which is what makes
 *     this bug so insidious.
 *   - Inside a non-static member function, an unqualified name finds the parameter first,
 *     then the member - so the parameter wins.
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
