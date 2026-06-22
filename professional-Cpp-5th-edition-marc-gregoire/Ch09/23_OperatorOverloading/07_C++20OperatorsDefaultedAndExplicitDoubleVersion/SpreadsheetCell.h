/*
 * Chapter 9 - C++20 Defaulted Comparisons Plus an Explicit double Version
 *
 * Combine defaulted SpreadsheetCell-vs-SpreadsheetCell comparisons with hand-rolled
 * overloads for `double` operands. This lets you skip the cost of building a
 * temporary SpreadsheetCell when the rhs is already a `double`, while still
 * letting the compiler maintain the all-cell comparisons for you.
 *
 * Key notes:
 *   - Once you declare `operator==(double)`, the compiler stops auto-defaulting
 *     `operator==(const SpreadsheetCell&)`. You must explicitly add `= default`
 *     for it, which is the line that this folder demonstrates.
 *   - `auto operator<=>(const SpreadsheetCell&) const = default;` still works -
 *     the explicit `operator<=>(double)` is a separate function, not a
 *     replacement.
 *   - You only need overloads for one direction (`SpreadsheetCell <op> double`).
 *     The C++20 rewrite rules let the compiler swap operands to reach the same
 *     function for `double <op> SpreadsheetCell`.
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
	[[nodiscard]] bool operator==(const SpreadsheetCell&) const = default;

	[[nodiscard]] bool operator==(double rhs) const;
	[[nodiscard]] std::partial_ordering operator<=>(double rhs) const;

private:
	static std::string doubleToString(double value);
	static double stringToDouble(std::string_view value);

	double m_value{ 0 };
};

SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator-(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator*(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
SpreadsheetCell operator/(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
