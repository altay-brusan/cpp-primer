/*
 * Chapter 9 - Default Arguments
 *
 * Defaults let one constructor or function accept a variable number of arguments
 * by supplying values for trailing parameters. `Spreadsheet(size_t width = 100,
 * size_t height = 100)` covers no-arg, one-arg, and two-arg calls in a single
 * declaration.
 *
 * Key notes:
 *   - Defaults must form a continuous tail of the parameter list. You cannot put
 *     a default on `width` while leaving `height` without one.
 *   - Defaults belong on the DECLARATION (the header), not on the definition.
 *     Callers must see the default when they compile the call site.
 *   - A constructor whose every parameter has a default value can act as the
 *     default constructor. Do NOT also declare a separate `Spreadsheet()` - the
 *     compiler will reject the ambiguity.
 *   - The `explicit` here prevents `Spreadsheet sheet = 5;` from working via a
 *     single-argument implicit conversion.
 */
#pragma once

#include "SpreadsheetCell.h"
#include <cstddef>

class Spreadsheet
{
public:
	explicit Spreadsheet(std::size_t width = 100, std::size_t height = 100);
	Spreadsheet(const Spreadsheet& src);
	~Spreadsheet();

	Spreadsheet& operator=(const Spreadsheet& rhs);

	void setCellAt(std::size_t x, std::size_t y, const SpreadsheetCell& cell);
	SpreadsheetCell& getCellAt(std::size_t x, std::size_t y);
	const SpreadsheetCell& getCellAt(std::size_t x, std::size_t y) const;

	void swap(Spreadsheet& other) noexcept;

private:
	void verifyCoordinate(std::size_t x, std::size_t y) const;

	std::size_t m_width{ 0 };
	std::size_t m_height{ 0 };
	SpreadsheetCell** m_cells{ nullptr };
};

void swap(Spreadsheet& first, Spreadsheet& second) noexcept;
