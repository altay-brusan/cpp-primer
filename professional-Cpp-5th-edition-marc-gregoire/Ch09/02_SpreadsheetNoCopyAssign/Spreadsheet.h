/*
 * Chapter 9 - Disallowing Assignment and Pass-by-Value
 *
 * When deep-copying a class is too expensive, too complicated, or simply does not
 * make sense, you can opt out entirely. Declaring the copy constructor and copy
 * assignment operator as `= delete` removes them from the overload set, so any
 * attempt to copy or pass-by-value becomes a compile error instead of a silent
 * shallow copy.
 *
 * Key notes:
 *   - `= delete` produces no body; the linker never looks for one because the
 *     compiler rejects every call site.
 *   - Once copy is deleted, pass-by-value, copy-construction, and `s1 = s2` all fail
 *     to compile.
 *   - The class is still usable: you can construct it, take references to it, and
 *     destroy it. Move operations, if you add any, are independent.
 */
#pragma once

#include "SpreadsheetCell.h"
#include <cstddef>

class Spreadsheet
{
public:
	Spreadsheet(std::size_t width, std::size_t height);
	Spreadsheet(const Spreadsheet& src) = delete;
	~Spreadsheet();

	Spreadsheet& operator=(const Spreadsheet& rhs) = delete;

	void setCellAt(std::size_t x, std::size_t y, const SpreadsheetCell& cell);
	SpreadsheetCell& getCellAt(std::size_t x, std::size_t y);

	void swap(Spreadsheet& other) noexcept;

private:
	void verifyCoordinate(std::size_t x, std::size_t y) const;

	std::size_t m_width{ 0 };
	std::size_t m_height{ 0 };
	SpreadsheetCell** m_cells{ nullptr };
};

void swap(Spreadsheet& first, Spreadsheet& second) noexcept;
