#pragma once

/*
 * Chapter 8 - When You Need a Default Constructor
 *
 * Same class as folder 10 - the lesson is in the driver, where building an array of cells
 * fails. Allocating an array of objects both reserves the contiguous storage and runs the
 * default constructor on every slot. There is no syntax to hand each slot a different
 * argument, so the compiler insists on a default constructor. This class has none (the two
 * user-defined constructors suppress the implicit one), so plain `SpreadsheetCell[3]` will
 * not compile.
 *
 * Key notes:
 *   - Defining any constructor disables the compiler-generated default constructor.
 *   - `SpreadsheetCell cells[3];` and `new SpreadsheetCell[10]` both demand a default
 *     constructor.
 *   - Aggregate-style initialization can side-step it: `SpreadsheetCell cells[3] { {0},
 *     {23}, {41} }` - but that only works when you can list every element by hand.
 *   - The cleaner fix is to add a default constructor; folder 12 does exactly that.
 */

#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(std::string_view initialValue);

	void setValue(double value);
	double getValue() const;

	void setString(std::string_view value);
	std::string getString() const;

private:
	std::string doubleToString(double value) const;
	double stringToDouble(std::string_view value) const;

	double m_value{ 0 };
};
