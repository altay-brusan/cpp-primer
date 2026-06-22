#pragma once

/*
 * Chapter 8 - Distinguishing Copying from Assignment
 *
 * Copy construction and copy assignment look similar but happen at different moments. If
 * the line looks like a declaration, it is calling a constructor - and an `=` in that
 * context is sugar for the copy constructor, not the assignment operator. Once an object
 * exists, the next time you put it on the left of `=` you are calling `operator=`.
 *
 * Key notes:
 *   - `T b { a };` and `T b = a;` both call the copy constructor of T.
 *   - `b = a;` after `b` already exists calls `operator=`.
 *   - Returning an object by value can build a temporary via the copy/move ctor; whether
 *     that temporary lands in a fresh local (copy ctor) or an existing object (operator=)
 *     depends on whether the destination is being declared or already exists.
 *   - Copy elision can erase the copy/move entirely; the language merely says these are
 *     the operations a compiler is allowed to invoke.
 */

#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
	SpreadsheetCell() = default;
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(std::string_view initialValue);
	SpreadsheetCell(const SpreadsheetCell& src);

	SpreadsheetCell& operator=(const SpreadsheetCell& rhs);

	void setValue(double value);
	double getValue() const;

	void setString(std::string_view value);
	std::string getString() const;

private:
	std::string doubleToString(double value) const;
	double stringToDouble(std::string_view value) const;

	double m_value{ 0 };
};
