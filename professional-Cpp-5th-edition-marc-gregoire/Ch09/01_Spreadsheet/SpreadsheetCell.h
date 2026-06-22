/*
 * Chapter 9 - The Spreadsheet Class (supporting type)
 *
 * SpreadsheetCell is the value type stored inside a Spreadsheet. It carries a single
 * `double` and offers converting constructors from `double` and `string_view`, which
 * is how implicit conversions later make `myCell + 5.6` work.
 *
 * Key notes:
 *   - Converting constructors mean a `double` or `string_view` argument can be silently
 *     promoted into a SpreadsheetCell - convenient, but cost a temporary object.
 *   - The non-static `doubleToString` / `stringToDouble` helpers are revised in later
 *     folders (static, then unnamed namespace).
 */
#pragma once

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
