#pragma once

/*
 * Chapter 8 - How to Write a Default Constructor
 *
 * A default constructor is just a constructor that can be called with no arguments. Once
 * you declare any constructor yourself, the implicit one disappears, so if you still want
 * `SpreadsheetCell c;` to work you have to write a default constructor explicitly. The
 * body can be empty here because the in-class initializer on `m_value` already provides
 * the starting state.
 *
 * Key notes:
 *   - "Default constructor" means zero-argument-callable, whether the compiler wrote it or
 *     you did.
 *   - With an in-class initializer like `m_value { 0 }`, the body of the default
 *     constructor can be empty.
 *   - Build a default-initialized stack object with `SpreadsheetCell c;` or
 *     `SpreadsheetCell c {};`. Never `SpreadsheetCell c();` - the "most vexing parse"
 *     turns that into a function declaration.
 *   - Free-store equivalent: `new SpreadsheetCell{}` or `make_unique<SpreadsheetCell>()`.
 */

#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
	SpreadsheetCell();
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
