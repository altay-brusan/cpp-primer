/*
 * Chapter 9 - static Member Functions
 *
 * A static member function belongs to the class, not to any particular instance.
 * It has no `this` pointer and cannot touch non-static data members through an
 * implicit receiver. Use it for helpers whose work has nothing to do with a
 * specific cell - here, the string<->double conversions are pure functions and
 * are promoted to `static`.
 *
 * Key notes:
 *   - Call from outside with the scope-resolution operator:
 *     `SpreadsheetCell::doubleToString(3.14)` if it were public.
 *   - From inside another member function you call it as `doubleToString(x)`, just
 *     like a regular function.
 *   - The `static` keyword appears only on the DECLARATION inside the class - not
 *     on the out-of-class definition.
 *   - You cannot mark a static member function `const` - there is no object to
 *     protect.
 *   - Access control still applies: a private static is callable only from within
 *     the class.
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
};
