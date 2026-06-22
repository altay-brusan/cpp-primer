/*
 * Chapter 9 - Move Constructor and Move Assignment in Terms of Swap
 *
 * The move ctor and move assignment can be written purely in terms of `swap()`,
 * which removes the cleanup() / moveFrom() helpers entirely. The move ctor swaps
 * a default-constructed `*this` with `src`; the move-assignment swaps `*this` with
 * a freshly-moved copy of `rhs`. Whatever ends up holding the old resources is
 * destroyed when its scope ends, doing the cleanup automatically.
 *
 * Key notes:
 *   - Add a new data member? Update swap() once; both move operations follow for free.
 *   - The move constructor begins by default-initializing `*this` (zero/null members),
 *     then swaps. After the swap, `*this` owns what was in `src` and `src` owns the
 *     null/zero state.
 *   - The move assignment is `auto moved{ std::move(rhs) }; swap(moved); return *this;`
 *     - the temporary `moved` takes the old contents and is destroyed on exit, freeing
 *     any old resources without manual cleanup.
 *   - swap() must be `noexcept`; the move operations rely on it never throwing.
 *   - This is the same copy-and-swap discipline used for copy assignment, applied to
 *     move.
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

	std::size_t m_width{ 0 };
	std::size_t m_height{ 0 };
	SpreadsheetCell** m_cells{ nullptr };
};

void swap(Spreadsheet& first, Spreadsheet& second) noexcept;
