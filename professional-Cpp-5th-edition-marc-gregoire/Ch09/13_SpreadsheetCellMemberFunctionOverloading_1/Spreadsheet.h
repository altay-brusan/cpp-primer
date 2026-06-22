/*
 * Chapter 9 - Overloading Member Functions Based on const (Scott Meyers pattern)
 *
 * `getCellAt()` is overloaded on the const-ness of `*this`: a non-const Spreadsheet
 * gets a `SpreadsheetCell&`, a const Spreadsheet gets a `const SpreadsheetCell&`.
 * Both overloads do the same work, so to avoid duplication this folder uses Scott
 * Meyers' `const_cast` pattern - the const overload contains the real logic, and
 * the non-const overload forwards to it through `std::as_const(*this)`, then
 * strips the const off the returned reference.
 *
 * Key notes:
 *   - You cannot overload on return type alone, but you CAN overload on the
 *     const-ness of the implicit `this` (i.e. by adding/removing the trailing
 *     `const`).
 *   - `std::as_const(*this)` (in <utility>) returns a const reference to *this,
 *     so the const overload of `getCellAt` is selected from inside the non-const
 *     overload.
 *   - The outer `const_cast<SpreadsheetCell&>(...)` removes the const we just
 *     added. This is safe only because we know *this is genuinely non-const.
 *   - Never go the other way: do NOT call the non-const overload from the const
 *     one - that would smuggle mutation into const code.
 *   - Folder 14 shows the alternate factoring with a private helper.
 *
 * Example:
 *     SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y) {
 *         return const_cast<SpreadsheetCell&>(
 *             as_const(*this).getCellAt(x, y));
 *     }
 */
#pragma once

#include "SpreadsheetCell.h"
#include <cstddef>

class Spreadsheet
{
public:
	Spreadsheet(std::size_t width, std::size_t height);
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
