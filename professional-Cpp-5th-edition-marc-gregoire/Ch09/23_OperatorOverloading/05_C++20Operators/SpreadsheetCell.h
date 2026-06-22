/*
 * Chapter 9 - C++20 Comparison Operators (<=> and ==)
 *
 * C++20 introduces the three-way comparison operator `<=>` (the spaceship), which
 * returns one of the ordering categories from <compare>. Implement `operator==`
 * and `operator<=>` as member functions, and the compiler automatically rewrites
 * `<`, `<=`, `>`, `>=`, and `!=` in terms of them.
 *
 * Key notes:
 *   - Recommended placement is now MEMBER, not free function. The compiler will
 *     swap operands and rewrite expressions like `10 == myCell` to
 *     `myCell == 10` to find your member overload.
 *   - The return type of `<=>` is one of `std::strong_ordering`,
 *     `std::weak_ordering`, or `std::partial_ordering`. Floating-point values
 *     are partial (`NaN` is unordered).
 *   - C++20 does NOT rewrite `==`/`!=` in terms of `<=>` for performance reasons;
 *     you still need the explicit `==`. Implementing `==` automatically gives you
 *     `!=`.
 *   - `[[nodiscard]]` on comparison operators stops the result from being
 *     accidentally thrown away.
 *   - Adding explicit overloads for `double` avoids the cost of building a
 *     temporary SpreadsheetCell when one operand is a plain `double`.
 *
 * Example:
 *     // One line gives you all six comparisons (with default behaviour) when the
 *     // class is comparable member-by-member:
 *     [[nodiscard]] auto operator<=>(const SpreadsheetCell&) const = default;
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

	[[nodiscard]] bool operator==(const SpreadsheetCell& rhs) const;
	[[nodiscard]] std::partial_ordering operator<=>(const SpreadsheetCell& rhs) const;

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
