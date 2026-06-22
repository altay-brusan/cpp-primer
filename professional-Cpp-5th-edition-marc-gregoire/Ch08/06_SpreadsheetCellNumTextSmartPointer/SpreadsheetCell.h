#pragma once

/*
 * Chapter 8 - Free-Store Objects with Smart Pointers
 *
 * Same class once more. The driver finally switches from raw `new`/`delete` to
 * `std::make_unique`, which is the right answer for owning a single dynamically-allocated
 * object. The unique_ptr destroys the cell automatically when it goes out of scope, so
 * there is no `delete` to forget and no leak path.
 *
 * Key notes:
 *   - `auto p = std::make_unique<SpreadsheetCell>();` is equivalent to wrapping
 *     `new SpreadsheetCell{}` in a `std::unique_ptr<SpreadsheetCell>`.
 *   - A `unique_ptr` still uses `->` for member access; it feels like a raw pointer with
 *     ownership baked in.
 *   - No manual `delete` is needed - destruction happens when the unique_ptr is destroyed.
 *
 * Example:
 *     // Same idea with shared ownership:
 *     auto sharedCell = std::make_shared<SpreadsheetCell>();
 */

#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
	void setValue(double value);
	double getValue() const;

	void setString(std::string_view value);
	std::string getString() const;

private:
	std::string doubleToString(double value) const;
	double stringToDouble(std::string_view value) const;

	double m_value{ 0 };
};
