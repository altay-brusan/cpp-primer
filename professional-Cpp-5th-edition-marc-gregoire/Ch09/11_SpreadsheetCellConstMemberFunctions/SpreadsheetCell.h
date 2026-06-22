/*
 * Chapter 9 - const Member Functions
 *
 * Putting `const` after the parameter list of a non-static member function is a
 * contract: this function promises not to modify the object's observable state.
 * The compiler enforces the promise by making every non-mutable data member look
 * like a reference-to-const inside the body.
 *
 * Key notes:
 *   - Only `const` member functions can be called on a `const` object, or through
 *     a const reference or const pointer.
 *   - You can call non-const members on a non-const object as usual.
 *   - The `const` is part of the function's signature - it must appear on both the
 *     declaration and the out-of-class definition.
 *   - Static member functions cannot be `const` (no object to protect).
 *   - Destructors cannot be `const`, even though `const` objects do get destroyed.
 *   - Get into the habit of marking every observer member function `const` -
 *     callers can then accept `const` references to your objects.
 *
 * Example:
 *     double getValue() const;       // declaration
 *     double SpreadsheetCell::getValue() const { return m_value; }
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
	static std::string doubleToString(double value);
	static double stringToDouble(std::string_view value);

	double m_value{ 0 };
};
