#pragma once

/*
 * Chapter 8 - Object Destruction (stack)
 *
 * A destructor is a member function named after the class, prefixed with `~`, with no
 * parameters and no return type. It runs automatically when an object dies. For locals,
 * that point is the closing brace of the enclosing block; for member subobjects, it is
 * when the containing object dies. Local objects are destroyed in the reverse of their
 * construction order, so `LIFO` is the rule.
 *
 * Key notes:
 *   - Signature: `~SpreadsheetCell();` - one per class, no overloads.
 *   - You usually do not need to write one - the compiler-generated destructor calls each
 *     member's destructor for you. Write one only when you own resources that need
 *     cleanup.
 *   - Local objects die in reverse declaration order at the end of their scope.
 *   - Member objects die in reverse declaration order, after the enclosing object's
 *     destructor body finishes.
 *   - Looking ahead: when a class is a polymorphic base, its destructor must be
 *     `virtual`, or `delete` through a base pointer is undefined behaviour. Chapter 10
 *     covers that in depth.
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

	// Destructor.
	~SpreadsheetCell();

	void setValue(double value);
	double getValue() const;

	void setString(std::string_view value);
	std::string getString() const;

private:
	std::string doubleToString(double value) const;
	double stringToDouble(std::string_view value) const;

	double m_value{ 0 };
};
