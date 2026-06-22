#pragma once

/*
 * Chapter 8 - Constructor Initializers (ctor-initializer list)
 *
 * A ctor-initializer (also called a member-initializer list) sits between the constructor
 * signature and its body, separated from them by a colon. Each entry constructs a base or
 * a data member directly, rather than first default-constructing it and then assigning to
 * it. That distinction matters for performance and is mandatory for a few kinds of
 * members.
 *
 * Key notes:
 *   - Syntax: `Class::Class(args) : member1 { expr }, member2 { expr } { body }`.
 *   - Members that MUST be initialized in the ctor-initializer (or in-class): `const`
 *     members, reference members, base classes without default constructors, and member
 *     objects whose class lacks a default constructor.
 *   - Members not listed are default-initialized before the body runs - so by the time
 *     you reach the body, every member is already alive.
 *   - For object data members, assignment in the body actually calls operator=, while a
 *     ctor-initializer calls the constructor directly; the latter is what you want.
 *   - Watch out: order of initialization follows the class-declaration order, not the
 *     order in the initializer list - the next folder demonstrates exactly this trap.
 *
 * Example:
 *     // Two equivalent ways to seed m_value, but the ctor-initializer is preferred.
 *     SpreadsheetCell::SpreadsheetCell(double v) : m_value { v } { }   // good
 *     SpreadsheetCell::SpreadsheetCell(double v) { m_value = v; }      // works, less clean
 */

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
	std::string doubleToString(double value) const;
	double stringToDouble(std::string_view value) const;

	double m_value{ 0 };
};
