#pragma once

/*
 * Chapter 8 - Using Objects: Objects on the Free Store
 *
 * Same class definition; the lesson is in the driver. Free-store allocation lets an object
 * outlive the scope it was created in, but every `new` you write must be balanced by a
 * matching `delete`. Forget the `delete` and the destructor never runs - you have leaked.
 *
 * Key notes:
 *   - Reach members of a pointer with the arrow operator: `myCellp->setValue(3.7);`.
 *   - A bare `SpreadsheetCell* p;` is undefined; always initialize to a real pointer or
 *     `nullptr`.
 *   - Free-store objects are explicit: nothing destroys them for you unless you call
 *     `delete` (or use a smart pointer, shown in folder 06).
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
