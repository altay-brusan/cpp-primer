/*
 * Chapter 9 - Overloading Member Functions Based on const (private-helper variant)
 *
 * Same goal as folder 13: provide both a `getCellAt() const` and a non-const
 * `getCellAt()`. This folder takes the alternate factoring - a private
 * `getCellAtHelper(...) const` does the real work, and both public overloads are
 * thin one-liners delegating to it. That avoids `const_cast` entirely; the cost is
 * one extra private declaration.
 *
 * Key notes:
 *   - The helper is itself `const` so it can be called on a `const Spreadsheet`.
 *   - Returning a `SpreadsheetCell&` from a `const` member function works here
 *     because the member is a pointer-to-pointer; the const member function is
 *     allowed to mutate what those pointers point to. (Use with care - here we
 *     immediately wrap the result in const for the public const overload.)
 *   - Pick this variant when you find the `const_cast` pattern (folder 13) too
 *     clever, or when the helper needs to return more than one thing.
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
	SpreadsheetCell& getCellAtHelper(std::size_t x, std::size_t y) const;

	void verifyCoordinate(std::size_t x, std::size_t y) const;

	std::size_t m_width{ 0 };
	std::size_t m_height{ 0 };
	SpreadsheetCell** m_cells{ nullptr };
};

void swap(Spreadsheet& first, Spreadsheet& second) noexcept;
