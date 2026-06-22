#pragma once

/*
 * Chapter 8 - Writing Constructors
 *
 * Constructors put an object into a sane state at birth. They have the same name as the
 * class, no return type, and they run automatically when an object is created. This
 * version of SpreadsheetCell ships two constructors - one that takes a numeric seed and
 * one that takes a text seed. Picking between them is overload resolution at the call
 * site.
 *
 * Key notes:
 *   - A constructor is named after the class and has no return type, not even `void`.
 *   - Multiple constructors are allowed as long as their parameter lists differ - this is
 *     ordinary overloading.
 *   - Construct stack objects directly: `SpreadsheetCell c { 5 };`. Do not "call" the
 *     constructor again later - `c.SpreadsheetCell(5);` is not valid C++.
 *   - Free-store objects use `new SpreadsheetCell{ args }`, smart-pointer objects use
 *     `make_unique<SpreadsheetCell>(args)`.
 *   - With these two constructors defined, the compiler no longer synthesises a default
 *     constructor - that bites in folder 11.
 *   - Avoid the trap of `SpreadsheetCell(...)` inside another constructor body - it builds
 *     a throwaway temporary, not the object you are initializing. Folder 18 introduces the
 *     proper tool: delegating constructors.
 *
 * Example:
 *     // Uniform initialization picks the right overload by argument type.
 *     SpreadsheetCell numeric { 4.4 };       // double-arg ctor
 *     SpreadsheetCell textual { "test" };    // string_view-arg ctor
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
