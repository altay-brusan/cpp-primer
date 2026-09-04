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
 *
 * 
 * This technique addresses a classic C++ design challenge: how to avoid
 * duplicating code when implementing both const and non-const versions of
 * the same member function.
 *
 * -----------------------------------------------------------------------------
 * The Problem: Code Duplication
 * -----------------------------------------------------------------------------
 * Imagine you need two versions of getCellAt:
 *   1. const SpreadsheetCell& getCellAt(...) const  (for const Spreadsheet&)
 *   2. SpreadsheetCell& getCellAt(...)        (for non-const Spreadsheet&)
 *
 * Both functions need to perform identical bounds checks and pointer arithmetic:
 *
 *   // ❌ DUPLICATED CODE IN BOTH OVERLOADS:
 *   SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y) {
 *       verifyCoordinate(x, y); // Bounds check
 *       return m_cells[x][y];
 *   }
 *
 *   const SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y) const {
 *       verifyCoordinate(x, y); // Identical bounds check!
 *       return m_cells[x][y];
 *   }
 *
 * If the validation logic grows complex, duplicating it is error-prone.
 *
 * -----------------------------------------------------------------------------
 * The Solution: A Private const Helper
 * -----------------------------------------------------------------------------
 * Share the logic without code duplication (and without const_cast) using a
 * single private helper method: getCellAtHelper(...) const.
 *
 *   // 1. PRIVATE HELPER (Contains ALL the validation/access logic):
 *   SpreadsheetCell& Spreadsheet::getCellAtHelper(size_t x, size_t y) const {
 *       verifyCoordinate(x, y);
 *       return m_cells[x][y]; // Returns non-const reference
 *   }
 *
 *   // 2. PUBLIC NON-CONST OVERLOAD:
 *   SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y) {
 *       return getCellAtHelper(x, y); // Simply delegates
 *   }
 *
 *   // 3. PUBLIC CONST OVERLOAD:
 *   const SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y) const {
 *       return getCellAtHelper(x, y); // Implicitly converts to const SpreadsheetCell&
 *   }
 *
 * -----------------------------------------------------------------------------
 * Deep Dive: How Pointer Constness Works Here (Shallow Constness)
 * -----------------------------------------------------------------------------
 * Member declaration: SpreadsheetCell** m_cells;
 * Inside a const member function:
 *   - The member pointer m_cells becomes a SpreadsheetCell** const (constant pointer).
 *   - The pointer itself cannot be reassigned (e.g., m_cells = nullptr is forbidden).
 *   - However, the data pointed to (**m_cells) is NOT made const by the compiler!
 *
 * Because C++ bitwise constness only protects m_cells itself, returning
 * m_cells[x][y] as a non-const reference (SpreadsheetCell&) is legally permitted.
 *
 * -----------------------------------------------------------------------------
 * How Each Public Overload Leverages the Helper:
 * -----------------------------------------------------------------------------
 * 1. Non-Const Public Call:
 *    Spreadsheet sheet{ 10, 10 };
 *    sheet.getCellAt(1, 2).setValue(5.0);
 *    -> Calls non-const getCellAt -> delegates to getCellAtHelper -> returns non-const ref.
 *
 * 2. Const Public Call:
 *    const Spreadsheet sheet{ 10, 10 };
 *    double val = sheet.getCellAt(1, 2).getValue();
 *    -> Calls const getCellAt -> delegates to getCellAtHelper -> converts to const ref.
 *    -> The public interface enforces read-only protection safely.
 *
 * -----------------------------------------------------------------------------
 * Comparison: Private Helper vs. const_cast Idiom:
 * -----------------------------------------------------------------------------
 * Strategy: Private Helper (Current Code)
 *   - Implementation: Private const helper returning non-const ref; public overloads delegate.
 *   - Pros: Zero casts; clean, standard C++ code.
 *   - Cons: Requires an extra private function declaration in the header.
 *
 * Strategy: const_cast Idiom
 *   - Implementation: Implement const overload, then have non-const overload call it
 *     using static_cast and const_cast.
 *   - Pros: No extra private helper method needed.
 *   - Cons: Uses const_cast and static_cast, which can be verbose and tricky to write.
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
