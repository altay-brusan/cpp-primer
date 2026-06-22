#pragma once

/*
 * Chapter 8 - Using Objects: Objects on the Stack
 *
 * Identical to the previous header. The point of this folder is the driver - it shows
 * the simplest way to make a SpreadsheetCell, namely declaring it as a local variable.
 * Stack objects are created and destroyed automatically as their enclosing block enters
 * and exits.
 *
 * Key notes:
 *   - Declaring `SpreadsheetCell myCell;` runs the default initialization right at the
 *     point of declaration - no `new` and no `delete` required.
 *   - Reach members on a stack object with the dot operator: `myCell.setValue(6);`.
 *   - Public data members work the same way, but exposing them is a design smell - reach
 *     for getters and setters instead.
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
