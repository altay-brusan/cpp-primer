/*
 * Chapter 9 - Enumerated Types Inside Classes
 *
 * Scoped enumerations (`enum class`) are strongly typed: their enumerators do NOT
 * leak into the surrounding scope, and there is no implicit conversion to or from
 * the underlying integer type. Putting one inside a class makes the enum part of
 * the class's interface; callers spell it `SpreadsheetCell::Color::Blue`.
 *
 * Key notes:
 *   - `enum class Color { Red = 1, Green, Blue, Yellow };` - the explicit `= 1`
 *     sets Red's underlying value; the rest follow as 2, 3, 4.
 *   - `enum class Color : underlying_type { ... }` lets you fix the storage type
 *     (for example, `enum class Color : uint8_t { ... }`).
 *   - Comparing `Color::Red` with an `int` is a compile error - that is the point.
 *     If you really need the integer, use `static_cast<int>(c)`.
 *   - Default-member initialization in the data section (`Color m_color{
 *     Color::Red };`) keeps every fresh cell red without writing a constructor body.
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

	void set(double value);
	void set(std::string_view value);

	double getValue() const;
	std::string getString() const;

	enum class Color { Red = 1, Green, Blue, Yellow };
	void setColor(Color color);
	Color getColor() const;

private:
	static std::string doubleToString(double value);
	static double stringToDouble(std::string_view value);

	double m_value{ 0 };
	Color m_color{ Color::Red };
};
