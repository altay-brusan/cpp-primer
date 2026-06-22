#pragma once

/*
 * Chapter 8 - Explicitly Defaulted Default Constructor
 *
 * Writing `SpreadsheetCell() = default;` tells the compiler "I still want the automatic
 * default constructor even though I have declared other constructors below." That keeps
 * you out of folder 11's array-creation trap without committing to an empty function body
 * spelled out in the .cpp.
 *
 * Key notes:
 *   - `= default` may appear in-class (as here) or in the implementation file.
 *   - The compiler-supplied body is the same one you would have written: no statements,
 *     and any in-class initializers run.
 *   - `= delete` is the partner spelling: write `SpreadsheetCell() = delete;` to forbid
 *     default construction entirely.
 *   - Once the default ctor is `= default`-ed, all the array and free-store idioms from
 *     folders 11 and 12 work again.
 */

#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
	SpreadsheetCell() = default;
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(std::string_view initialValue);

	void setValue(double value);
	double getValue() const;

	void setString(std::string_view value);
	std::string getString() const;

private:
	std::string doubleToString(double value) const;
	double stringToDouble(std::string_view value) const;

	double m_value{ 0 };
};
