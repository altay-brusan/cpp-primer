/*
 * Chapter 10 - Polymorphic Spreadsheet (abstract base)
 *
 * SpreadsheetCell is now an *abstract base class*. Both members are pure
 * virtual (`= 0`), so:
 *   - SpreadsheetCell cannot be instantiated directly.
 *   - Every concrete subclass must provide its own `set()` and `getString()`.
 *
 * Key notes:
 *   - The virtual destructor is required because cells will be deleted through
 *     `SpreadsheetCell*` (the test driver uses `unique_ptr<SpreadsheetCell>`).
 *   - This header has no .cpp; pure virtual declarations need no out-of-class
 *     definition unless you actually want a fallback implementation (see the
 *     09_PureVirtualMemberFunctionImplementations sample for that case).
 *   - The two subclasses (DoubleSpreadsheetCell, StringSpreadsheetCell) are
 *     interchangeable through a SpreadsheetCell& - the heart of polymorphism.
 */
#pragma once

#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
	virtual ~SpreadsheetCell() = default;

	virtual void set(std::string_view value) = 0;

	virtual std::string getString() const = 0;
};
