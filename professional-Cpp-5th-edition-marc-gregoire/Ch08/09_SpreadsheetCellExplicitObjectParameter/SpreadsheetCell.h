#pragma once

/*
 * Chapter 8 - Explicit Object Parameter (C++23)
 *
 * C++23 lets a member function name the implicit object explicitly as its first parameter,
 * tagged with the `this` keyword. Inside the body, the chosen name (here `self`) plays the
 * role that `this` would otherwise play. You can choose its type - `&`, `const&`, or even
 * a template parameter - which opens the door to "deducing this" patterns.
 *
 * Key notes:
 *   - Spelling is `void func(this SpreadsheetCell& self, ...)`. The `this` keyword is in
 *     parameter position - it is not a hidden pointer here.
 *   - Inside such a function, you reach members through `self.member`, not `this->member`.
 *   - The explicit object parameter only goes on the declaration; the definition repeats
 *     it.
 *   - Other member functions in the same class can keep the classic implicit-`this` form
 *     side by side.
 */

#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
	void setValue(this SpreadsheetCell& self, double value);
	double getValue() const;

	void setString(std::string_view value);
	std::string getString() const;

private:
	std::string doubleToString(double value) const;
	double stringToDouble(std::string_view value) const;

	double m_value{ 0 };
};
