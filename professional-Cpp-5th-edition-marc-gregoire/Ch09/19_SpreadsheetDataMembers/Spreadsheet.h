/*
 * Chapter 9 - Different Kinds of Data Members
 *
 * The Spreadsheet here grows several flavors of data member at once:
 *   - `const size_t m_id{ 0 };` - per-instance constant, set once in the
 *     ctor-initializer, never reassigned. Makes the class unassignable unless you
 *     skip copying the id (which is what the copy-assign via copy-and-swap does).
 *   - `const SpreadsheetApplication& m_theApp;` - a reference data member. Must be
 *     bound in the ctor-initializer; cannot be rebound, which is also why the
 *     copy assignment operator must avoid touching it.
 *   - `static inline std::size_t ms_counter{ 0 };` - a C++17 inline static data
 *     member. The `inline` means storage is provided here in the header; no
 *     separate `size_t Spreadsheet::ms_counter;` definition is needed in the .cpp.
 *   - `static constexpr std::size_t MaxHeight{ 100 };` - class-scope compile-time
 *     constant; usable as a default argument and as an array bound.
 *
 * Key notes:
 *   - In-class default member initializers (`m_width{ 0 }`) avoid the "uninitialized
 *     POD" trap; you only need to override them in the ctor-initializer when you
 *     have a non-default value.
 *   - Once a class has a reference or `const` data member, the compiler will
 *     not synthesize a copy assignment operator; you must either implement one
 *     (e.g. via copy-and-swap) or delete it.
 *   - Replacing the pre-C++17 declaration+definition pair with `static inline` is
 *     a one-line modernization win and lives entirely in the header.
 *   - `static constexpr` integral/enum members can be used inside the class
 *     definition itself (here as default-argument values).
 */
#pragma once

#include "SpreadsheetCell.h"
#include <cstddef>

class SpreadsheetApplication { };

class Spreadsheet
{
public:
	Spreadsheet(std::size_t width, std::size_t height,
		const SpreadsheetApplication& theApp);
	Spreadsheet(const Spreadsheet& src);
	~Spreadsheet();
	Spreadsheet& operator=(const Spreadsheet& rhs);

	void setCellAt(std::size_t x, std::size_t y, const SpreadsheetCell& cell);
	SpreadsheetCell& getCellAt(std::size_t x, std::size_t y);
	const SpreadsheetCell& getCellAt(std::size_t x, std::size_t y) const;

	std::size_t getId() const;

	void swap(Spreadsheet& other) noexcept;

	static constexpr std::size_t MaxHeight{ 100 };
	static constexpr std::size_t MaxWidth{ 100 };

private:
	void verifyCoordinate(std::size_t x, std::size_t y) const;

	const std::size_t m_id{ 0 };
	std::size_t m_width{ 0 };
	std::size_t m_height{ 0 };
	SpreadsheetCell** m_cells{ nullptr };

	const SpreadsheetApplication& m_theApp;

	//static std::size_t ms_counter; // Pre C++17
	static inline std::size_t ms_counter{ 0 }; // Since C++17
};

void swap(Spreadsheet& first, Spreadsheet& second) noexcept;
