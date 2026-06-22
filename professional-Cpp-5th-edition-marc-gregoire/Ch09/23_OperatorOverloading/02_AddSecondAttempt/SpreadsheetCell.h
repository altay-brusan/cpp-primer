/*
 * Chapter 9 - Operator Overloading: Second Attempt with operator+ as a Member
 *
 * Rename `add` to `operator+`. The compiler now translates `myCell + anotherCell`
 * into `myCell.operator+(anotherCell)`, which feels far more natural at call sites.
 *
 * Key notes:
 *   - `SpreadsheetCell operator+(const SpreadsheetCell& cell) const;` - same shape
 *     as `add`, just a different name.
 *   - When you write `myCell + 5.6`, the compiler implicitly constructs a
 *     temporary SpreadsheetCell from `5.6` because there is a non-explicit
 *     converting constructor.
 *   - There is one painful limitation of the member form: the left operand must
 *     be a SpreadsheetCell. `5.6 + myCell` does NOT compile here. Folder 3 fixes
 *     that with a free-function operator+.
 *   - You can declare a `SpreadsheetCell operator+(double rhs) const` overload
 *     to skip the temporary creation when the rhs is a `double`.
 *
 * Example:
 *     SpreadsheetCell aThirdCell{ myCell + anotherCell };
 *     // Equivalent to: SpreadsheetCell aThirdCell{ myCell.operator+(anotherCell) };
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

	void set(double value);
	void set(std::string_view value);

	double getValue() const;
	std::string getString() const;

	SpreadsheetCell operator+(const SpreadsheetCell& cell) const;
	//SpreadsheetCell operator+(double rhs) const;

private:
	static std::string doubleToString(double value);
	static double stringToDouble(std::string_view value);

	double m_value{ 0 };
};
