/*
 * Chapter 9 - Stable Interface via the pimpl Idiom
 *
 * The pimpl ("pointer to implementation") idiom hides every data member and every
 * private detail behind a forward-declared nested `Impl` class. The public class
 * carries one data member - a `unique_ptr<Impl>` - and forwards each public method
 * to the implementation. Clients only ever see the stable header, so changes to
 * the implementation do not force them to recompile.
 *
 * Key notes:
 *   - `class Impl;` is only forward-declared in the header. Its definition lives
 *     in the .cpp, invisible to callers.
 *   - Because `Impl` is incomplete in the header, the destructor, move ctor, and
 *     move assignment cannot be defaulted IN the header. They must be defaulted
 *     (or implemented) in the .cpp, after `Impl` becomes complete.
 *   - The interface class has to forward every public operation: setCellAt,
 *     getCellAt, getId, swap, the copy operations - each is a one-line shim.
 *   - Copy semantics need an explicit deep copy: `m_impl{ make_unique<Impl>(*src.m_impl) }`.
 *     Otherwise the inner unique_ptr would refuse to copy.
 *   - The benefit is binary stability: rearranging Impl's data members does not
 *     change the size or layout of Spreadsheet, so no caller needs rebuilding.
 *   - This is also called the bridge pattern or "Cheshire Cat" idiom.
 */
#pragma once

#include "SpreadsheetCell.h"
#include <cstddef>
#include <memory>

class Spreadsheet
{
public:
	explicit Spreadsheet(std::size_t width = MaxWidth, std::size_t height = MaxHeight);
	Spreadsheet(const Spreadsheet& src);
	Spreadsheet(Spreadsheet&&) noexcept;
	~Spreadsheet();

	Spreadsheet& operator=(const Spreadsheet& rhs);
	Spreadsheet& operator=(Spreadsheet&&) noexcept;
	
	void setCellAt(std::size_t x, std::size_t y, const SpreadsheetCell& cell);
	SpreadsheetCell& getCellAt(std::size_t x, std::size_t y);
	const SpreadsheetCell& getCellAt(std::size_t x, std::size_t y) const;
	
	std::size_t getId() const;

	static constexpr std::size_t MaxHeight{ 100 };
	static constexpr std::size_t MaxWidth{ 100 };

	void swap(Spreadsheet& other) noexcept;

private:
	class Impl;
	std::unique_ptr<Impl> m_impl;
};

void swap(Spreadsheet& first, Spreadsheet& second) noexcept;
