#pragma once

/*
 * Chapter 8 - Objects on the Free Store (arrow vs. dereference-and-dot)
 *
 * Identical class. The driver in this folder spells out `(*ptr).member` instead of
 * `ptr->member` to make the point that `->` is just sugar over a deref followed by a dot.
 * The arrow form is the idiomatic choice; the parenthesized form is there to demystify it,
 * not to imitate.
 *
 * Key notes:
 *   - `p->m` and `(*p).m` produce the same expression; `->` is preferred for readability.
 *   - The parenthesization in `(*p).m` is needed because `.` binds tighter than the unary
 *     `*`.
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
