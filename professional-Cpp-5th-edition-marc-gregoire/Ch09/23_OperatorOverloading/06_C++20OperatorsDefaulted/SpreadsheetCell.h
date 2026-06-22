/*
 * Chapter 9 - C++20 Defaulted Comparison Operators
 *
 * If `operator==` and `operator<=>` would simply compare each data member in turn,
 * the compiler can write them for you. Just default them with `= default`. The
 * compiler will keep them up to date as new data members are added.
 *
 * Key notes:
 *   - `[[nodiscard]] auto operator<=>(const SpreadsheetCell&) const = default;` -
 *     return type is deduced from the data members. Here it works out to
 *     `std::partial_ordering` because the only data member is `double`.
 *   - Defaulting `operator<=>` also implicitly defaults `operator==` - but only if
 *     no user-declared `operator==` exists.
 *   - Defaulted operators must take a `const T&` parameter where T is the class.
 *     `auto operator<=>(double) const = default;` will NOT compile.
 *   - Adding ANY user-declared `operator==(double)` (folder 7) suppresses the
 *     implicit defaulted `operator==(const SpreadsheetCell&)`. You must default
 *     it explicitly in that case.
 *   - Prefer defaulted operators when feasible - any future field is compared
 *     automatically without code changes.
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
