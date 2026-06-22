/*
 * Chapter 9 - Operator Overloading: First Attempt with add()
 *
 * Before reaching for `operator+`, the natural starting point is a regular member
 * function: `SpreadsheetCell add(const SpreadsheetCell& cell) const`. It does the
 * job, but every call site reads `a.add(b)` instead of `a + b`. This folder shows
 * the version we are about to improve.
 *
 * Key notes:
 *   - `add` is `const` and returns a new SpreadsheetCell; the operands are not
 *     modified.
 *   - The right-hand operand is taken by const reference to avoid a copy.
 *   - The next folder replaces `add` with an `operator+` member function.
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

	SpreadsheetCell add(const SpreadsheetCell& cell) const;

private:
	static std::string doubleToString(double value);
	static double stringToDouble(std::string_view value);

	double m_value{ 0 };
};
