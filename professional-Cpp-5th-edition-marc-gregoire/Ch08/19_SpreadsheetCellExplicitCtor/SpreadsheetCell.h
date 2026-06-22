#pragma once

/*
 * Chapter 8 - Explicit Constructors
 *
 * Any constructor callable with a single argument doubles as a converting constructor:
 * the compiler will silently convert that argument type into your class wherever a
 * SpreadsheetCell is expected. Mark the constructor `explicit` to block that implicit
 * step - callers will then have to spell the conversion out themselves. Here the
 * `string_view` constructor is `explicit`, so `myCell = "6"sv;` will no longer compile,
 * while the un-tagged double constructor still allows `myCell = 5;`.
 *
 * Key notes:
 *   - `explicit` belongs on the declaration inside the class, not on the out-of-class
 *     definition.
 *   - Marking single-arg ctors `explicit` is a defensive default - it prevents accidental
 *     conversions from sneaking through.
 *   - Implicit conversions still happen during initialization with `=` of the same type;
 *     `explicit` only stops them at function-call / assignment boundaries that need a
 *     conversion.
 *   - The companion folder 20 covers `explicit(bool)` and explicit on multi-arg ctors.
 *
 * Example:
 *     // With the explicit qualifier in place, you must opt in to the conversion:
 *     myCell = SpreadsheetCell { "6"sv };
 */

#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
	SpreadsheetCell() = default;
	SpreadsheetCell(double initialValue);
	explicit SpreadsheetCell(std::string_view initialValue);
	SpreadsheetCell(const SpreadsheetCell& src);

	void setValue(double value);
	double getValue() const;

	void setString(std::string_view value);
	std::string getString() const;

private:
	std::string doubleToString(double value) const;
	double stringToDouble(std::string_view value) const;

	double m_value{ 0 };
};
