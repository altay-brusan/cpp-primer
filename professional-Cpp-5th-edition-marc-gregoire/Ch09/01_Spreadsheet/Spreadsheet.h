/*
 * Chapter 9 - Dynamic Memory Allocation in Objects
 *
 * A Spreadsheet owns a two-dimensional array of SpreadsheetCells that is sized at run time,
 * so it allocates memory in its constructor. Anything that allocates in its constructor
 * must also free that memory in its destructor and decide how to behave when copied or
 * assigned, otherwise a shallow copy will leave two objects sharing the same buffer and
 * a dangling pointer once one of them goes out of scope.
 *
 * Key notes:
 *   - m_cells is a SpreadsheetCell** - an array of pointers, each pointing to one column
 *     of cells. C++ has no built-in `new T[w][h]` form, so the inner arrays are allocated
 *     in a loop.
 *   - Rule of Three: if you write a destructor, you almost certainly need a copy
 *     constructor and a copy assignment operator too. Default versions do shallow copies
 *     and break when raw pointers own memory.
 *   - The copy assignment operator uses the copy-and-swap idiom: build a temporary copy,
 *     swap with `*this`, return. Strong exception safety with no manual self-assignment
 *     check needed.
 *   - `swap()` is marked `noexcept` so it can serve as the commit step that cannot fail.
 *   - A non-member `swap()` is provided so Standard Library algorithms can find it via ADL.
 *   - In production, prefer `std::vector<std::vector<SpreadsheetCell>>` (rule of zero).
 *     The raw pointer is kept here to demonstrate the manual machinery.
 *
 * Example:
 *     // Two-dimensional allocation idiom:
 *     m_cells = new SpreadsheetCell*[m_width];
 *     for (size_t i{ 0 }; i < m_width; ++i)
 *         m_cells[i] = new SpreadsheetCell[m_height];
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

	void swap(Spreadsheet& other) noexcept;

private:
	void verifyCoordinate(std::size_t x, std::size_t y) const;
	//bool inRange(std::size_t value, std::size_t upper) const;

	std::size_t m_width{ 0 };
	std::size_t m_height{ 0 };
	SpreadsheetCell** m_cells{ nullptr };
};

void swap(Spreadsheet& first, Spreadsheet& second) noexcept;
