/*
 * Chapter 10 - Polymorphic Spreadsheet (numeric cell)
 *
 * Concrete subclass storing a `std::optional<double>`. Implements the abstract
 * interface from SpreadsheetCell and adds its own typed `set(double)` /
 * `getValue()` overloads on top.
 *
 * Key notes:
 *   - The string overload of `set` is the one that *overrides* the base. The
 *     double overload is just an additional, type-specific entry point.
 *   - `std::from_chars` is the no-allocate, no-locale parse - prefer it over
 *     `std::stod`/`std::strtod` for numeric input.
 *   - `std::optional<double>` makes "no value yet" distinct from "zero", which
 *     matters when `getString()` returns an empty string for the empty case.
 *   - Helpers are `static` because they don't touch any per-object state.
 *   - The free `operator+` lives at the bottom and is defined in the .cpp.
 */
#pragma once

#include "SpreadsheetCell.h"
#include <optional>
#include <string>
#include <string_view>
#include <charconv>

class DoubleSpreadsheetCell : public SpreadsheetCell
{
public:
	virtual void set(double value)
	{
		m_value = value;
	}

	virtual double getValue() const
	{
		return m_value.value_or(0);
	}

	void set(std::string_view value) override
	{
		m_value = stringToDouble(value);
	}

	std::string getString() const override
	{
		return (m_value.has_value() ? doubleToString(m_value.value()) : "");
	}

private:
	static std::string doubleToString(double value)
	{
		return std::to_string(value);
	}

	static double stringToDouble(std::string_view value)
	{
		double number{ 0 };
		std::from_chars(value.data(), value.data() + value.size(), number);
		return number;
	}

	std::optional<double> m_value;
};

DoubleSpreadsheetCell operator+(const DoubleSpreadsheetCell& lhs,
	const DoubleSpreadsheetCell& rhs);
