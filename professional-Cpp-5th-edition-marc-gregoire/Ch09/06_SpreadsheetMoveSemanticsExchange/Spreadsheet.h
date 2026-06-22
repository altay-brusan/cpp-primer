/*
 * Chapter 9 - Implementing Move Semantics with std::exchange
 *
 * Same move ctor / move assignment surface as the previous folder, but with
 * `moveFrom()` rewritten to use `std::exchange`. The shape of the class is identical;
 * only the helper changes.
 *
 * Key notes:
 *   - `m_cells = std::exchange(src.m_cells, nullptr);` reads the source pointer and
 *     nulls it in one expression.
 *   - The pattern compresses three "copy then reset" lines per member into one each,
 *     and the result is still trivially noexcept because the operations are
 *     primitive assignments.
 *   - The header still keeps the cleanup() and moveFrom() helpers for clarity.
 */
#pragma once

#include "SpreadsheetCell.h"
#include <cstddef>

class Spreadsheet
{
public:
	Spreadsheet(std::size_t width, std::size_t height);
	Spreadsheet(const Spreadsheet& src);
	Spreadsheet(Spreadsheet&& src) noexcept; // Move constructor
	~Spreadsheet();

	Spreadsheet& operator=(const Spreadsheet& rhs);
	Spreadsheet& operator=(Spreadsheet&& rhs) noexcept;  // Move assignment

	void setCellAt(std::size_t x, std::size_t y, const SpreadsheetCell& cell);
	SpreadsheetCell& getCellAt(std::size_t x, std::size_t y);

	void swap(Spreadsheet& other) noexcept;

private:
	void verifyCoordinate(std::size_t x, std::size_t y) const;
	void cleanup() noexcept;
	void moveFrom(Spreadsheet& src) noexcept;

	std::size_t m_width{ 0 };
	std::size_t m_height{ 0 };
	SpreadsheetCell** m_cells{ nullptr };
};

void swap(Spreadsheet& first, Spreadsheet& second) noexcept;
