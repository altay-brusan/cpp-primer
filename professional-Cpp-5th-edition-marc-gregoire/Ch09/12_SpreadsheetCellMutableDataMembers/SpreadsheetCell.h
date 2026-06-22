/*
 * Chapter 9 - mutable Data Members
 *
 * Sometimes a function is logically const - it does not change anything the user
 * cares about - but it does need to touch a private bookkeeping field, like an
 * access counter, a cached lazy value, or a synchronization primitive. Marking
 * the affected field `mutable` permits modification even inside `const` member
 * functions, without lying to the rest of the class.
 *
 * Key notes:
 *   - `mutable size_t m_numAccesses{ 0 };` is writable even from `double getValue()
 *     const`.
 *   - Reach for `mutable` for caches, lazy initialization, profiling counters, or a
 *     `std::mutex` that has to be locked from a `const` reader function.
 *   - Do NOT use `mutable` to escape `const`-ness when the change is observable to
 *     callers - that breaks the contract.
 */
#pragma once

#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
	SpreadsheetCell() = default;
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(std::string_view initialValue);
	
	void setValue(double value);
	double getValue() const;

	void setString(std::string_view value);
	std::string getString() const;

private:
	static std::string doubleToString(double value);
	static double stringToDouble(std::string_view value);

	double m_value{ 0 };
	mutable unsigned m_numAccesses{ 0 };
};
