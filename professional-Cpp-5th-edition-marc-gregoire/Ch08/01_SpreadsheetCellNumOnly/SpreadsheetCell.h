#pragma once

/*
 * Chapter 8 - Writing Classes (first SpreadsheetCell)
 *
 * The first cut at SpreadsheetCell - one numeric field, two member functions to set and read
 * it. Each object gets its own copy of the data members, while the member functions are
 * shared across all objects. Mark any member function that does not change observable
 * state as const so it can be called on const objects and const references.
 *
 * Key notes:
 *   - A class definition is a declaration and ends with a semicolon.
 *   - The default access level for a class is private; for a struct it is public. That is
 *     the only meaningful difference between the two.
 *   - Member functions that do not mutate the object should be declared const, like
 *     `getValue() const`.
 *   - Prefer initializing data members in-class (`double m_value { 0 };`) so every ctor
 *     starts from a known state.
 *   - A data member cannot share a name with a member function in the same class.
 */

class SpreadsheetCell
{
public:
	void setValue(double value);
	double getValue() const;       // const - this member function promises not to mutate the cell

private:
	double m_value{ 0 };           // in-class initializer - always start from a known value
};

//export class SpreadsheetCell
//{
//public:
//	void setValue(double value) { m_value = value; }
//	double getValue() const { return m_value; }
//private:
//	double m_value{ 0 };
//};
