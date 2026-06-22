#pragma once

/*
 * Chapter 8 - Assignment Operator (copy assignment)
 *
 * Copy assignment overwrites an existing object with the contents of another. The
 * canonical signature is
 *     SpreadsheetCell& operator=(const SpreadsheetCell& rhs);
 * Return-by-reference so that assignments can chain (`a = b = c;`). Almost every copy
 * assignment operator should also guard against self-assignment - `if (this == &rhs)
 * return *this;` - and then copy each member from `rhs`.
 *
 * Key notes:
 *   - Signature: `Class& operator=(const Class& rhs);`. Return-by-reference is what
 *     enables chaining.
 *   - Always return `*this` at the end.
 *   - Check for self-assignment up front. For a class holding only value-typed members
 *     it is a harmless no-op; once raw-resource ownership shows up (Chapter 9) the check
 *     becomes essential.
 *   - Copy assignment != copy construction. Copy construction builds a brand-new object;
 *     assignment overwrites an existing, fully constructed one.
 *   - The compiler-generated copy assignment operator does member-wise `operator=` calls.
 *     Default it (`= default`) or delete it (`= delete`) when that fits.
 *   - C++11 deprecates the implicit generation when you have a user-declared destructor
 *     or copy constructor - say `= default` explicitly if you still want it.
 */

#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
	SpreadsheetCell() = default;
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(std::string_view initialValue);
	SpreadsheetCell(const SpreadsheetCell& src);

	SpreadsheetCell& operator=(const SpreadsheetCell& rhs);

	void setValue(double value);
	double getValue() const;

	void setString(std::string_view value);
	std::string getString() const;

private:
	std::string doubleToString(double value) const;
	double stringToDouble(std::string_view value) const;

	double m_value{ 0 };
};
