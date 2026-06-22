/*
 * Chapter 9 - Unnamed Namespace for Implementation Helpers
 *
 * The `doubleToString` and `stringToDouble` helpers used to be private static
 * member functions. They never touched any cell state, so there is no good reason
 * for them to be members at all. Move them into an unnamed (anonymous) namespace
 * inside the .cpp - they become translation-unit-local free functions, the header
 * stays clean, and clients of the header never even know they exist.
 *
 * Key notes:
 *   - Anything inside `namespace { ... }` in a .cpp has internal linkage and is
 *     invisible to other translation units.
 *   - This is the modern replacement for the old `static` linkage trick at file
 *     scope.
 *   - The class declaration here loses the two helper declarations entirely.
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
	double m_value{ 0 };
};
