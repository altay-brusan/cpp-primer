/*
 * Chapter 12 - SpreadsheetCell (template-friendly helper)
 *
 * Streamlined SpreadsheetCell used as `T` inside `Grid<T>`. The only addition
 * versus the earlier chapters is the defaulted `operator<=>` (the three-way
 * comparison operator from C++20) so cells become orderable for `std::sort`
 * and friends without writing six relational operators by hand.
 *
 * Anything stored in a Grid needs:
 *   - copy semantics (defaulted here).
 *   - if you ever default-construct a stored optional<T> with a value,
 *     T needs a default ctor too.
 *
 * `[[nodiscard]]` on `operator<=>` is harmless decoration; comparison
 * results shouldn't be silently thrown away.
 */
#pragma once

#include <string>
#include <string_view>
#include <compare>

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

	SpreadsheetCell& operator+=(const SpreadsheetCell& rhs);
	SpreadsheetCell& operator-=(const SpreadsheetCell& rhs);
	SpreadsheetCell& operator*=(const SpreadsheetCell& rhs);
	SpreadsheetCell& operator/=(const SpreadsheetCell& rhs);

	[[nodiscard]] auto operator<=>(const SpreadsheetCell&) const = default;

private:
	static std::string doubleToString(double value);
	static double stringToDouble(std::string_view value);

	double m_value{ 0 };
};

SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator-(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator*(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator/(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
