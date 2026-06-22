/*
 * Chapter 9 - Implementing Move Semantics
 *
 * A move constructor and move assignment operator transfer ownership of resources
 * from a soon-to-be-destroyed source into a freshly built or pre-existing target.
 * They use rvalue-reference parameters (`Spreadsheet&&`) so the compiler picks them
 * automatically when the source is a temporary or has been cast with `std::move`.
 * The source is left in a valid but unspecified state - typically null pointers and
 * zeroed sizes - so its destructor still runs harmlessly.
 *
 * Key notes:
 *   - Move operations should be marked `noexcept`. Standard containers like
 *     `std::vector` only move-construct your objects on reallocation when they
 *     promise not to throw; otherwise they copy.
 *   - This implementation uses two helpers: `cleanup()` releases the current
 *     resources, `moveFrom(src)` shallow-copies the pointers and zeroes the source.
 *   - Rule of Five: if you write any of {destructor, copy ctor, copy=, move ctor,
 *     move=}, you usually need to declare or default all five.
 *   - Always test `this == &rhs` in the move-assignment operator before calling
 *     `cleanup()` - `sheet1 = std::move(sheet1)` should not blow up.
 *   - The default move constructor/assignment are generated only when the class has
 *     no user-declared copy/move/destructor.
 *
 * Example:
 *     // Typical move-ctor body, leaving the source empty:
 *     Spreadsheet::Spreadsheet(Spreadsheet&& src) noexcept { moveFrom(src); }
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
