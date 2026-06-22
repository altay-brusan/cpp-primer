#pragma once

/*
 * Chapter 8 - Delegating Constructors
 *
 * A constructor can forward to another constructor of the same class - that is a
 * delegating constructor. The delegated-to constructor runs in full, including its
 * ctor-initializer, and only when it returns does the delegating constructor's body run.
 * This is how you reuse construction logic without copy-pasting member initialization.
 *
 * Key notes:
 *   - Spelling lives in the ctor-initializer: `: SpreadsheetCell { ... }`. It cannot
 *     appear in the body, and it must be the only entry in the initializer list.
 *   - The target constructor completes the object's initialization; the delegating
 *     constructor's body is just any extra work to do afterwards.
 *   - Cycles in delegation are undefined behaviour - do not let `A -> B -> A` happen.
 *   - Delegating is the right cure for the "I want to call my own constructor from
 *     another" itch that folder 10's note warned against.
 *
 * Example:
 *     // Delegating from the string ctor to the double ctor:
 *     SpreadsheetCell::SpreadsheetCell(string_view s)
 *         : SpreadsheetCell { stringToDouble(s) } { }
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
