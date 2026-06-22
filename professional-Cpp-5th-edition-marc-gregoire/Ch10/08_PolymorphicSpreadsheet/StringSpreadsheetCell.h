/*
 * Chapter 10 - Polymorphic Spreadsheet (string cell)
 *
 * Stores a `std::optional<std::string>`. Notice the converting constructor
 * from `DoubleSpreadsheetCell`: that's how the test driver can build a
 * StringSpreadsheetCell from a DoubleSpreadsheetCell on the right side of `+`
 * - without any operator+ overload that mixes the two types.
 *
 * Key notes:
 *   - The `StringSpreadsheetCell(const DoubleSpreadsheetCell&)` ctor lets the
 *     compiler implicitly convert a DoubleSpreadsheetCell into a
 *     StringSpreadsheetCell when needed. In the test you see this exact
 *     conversion drive `stringCell + doubleCell`.
 *   - Defaulted default constructor keeps the empty cell trivially constructible.
 *   - The free operator+ at the bottom is symmetric with the one in
 *     DoubleSpreadsheetCell.h - both live as non-members for the same reason.
 */
#pragma once

#include "SpreadsheetCell.h"
#include "DoubleSpreadsheetCell.h"
#include <optional>
#include <string>
#include <string_view>

class StringSpreadsheetCell : public SpreadsheetCell
{
public:
	StringSpreadsheetCell() = default;

	StringSpreadsheetCell(const DoubleSpreadsheetCell& cell)
		: m_value{ cell.getString() }
	{
	}

	void set(std::string_view value) override
	{
		m_value = value;
	}

	std::string getString() const override
	{
		return m_value.value_or("");
	}

private:
	std::optional<std::string> m_value;
};

StringSpreadsheetCell operator+(const StringSpreadsheetCell& lhs,
	const StringSpreadsheetCell& rhs);
