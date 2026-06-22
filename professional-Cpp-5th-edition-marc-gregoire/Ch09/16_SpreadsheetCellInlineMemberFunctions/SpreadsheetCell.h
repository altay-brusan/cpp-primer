/*
 * Chapter 9 - inline Member Functions
 *
 * `inline` is a hint that the compiler may replace a call with the function body
 * at the call site rather than emitting a real call. The hint can be ignored - and
 * with modern optimizers and link-time code generation, often is. The keyword is
 * still useful for one thing: it relaxes the One Definition Rule, allowing the
 * function definition to appear in multiple translation units.
 *
 * Key notes:
 *   - Any function definition you put inside a class body is implicitly inline.
 *     Same for functions defined in the header.
 *   - If you split an inline member function into a separate definition, that
 *     definition must still be visible in every translation unit that calls it -
 *     usually that means: keep it in the header.
 *   - Compilers ignore the hint for functions that are too complex, recursive,
 *     virtual through indirection, or otherwise unprofitable to inline.
 *   - Marking trivial getters inline can shave a function call, but trust the
 *     optimizer for most cases.
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

	/*
	double getValue() const;
	std::string getString() const;
	*/

	inline double getValue() const
	{
		++m_numAccesses;
		return m_value;
	}

	inline std::string getString() const
	{
		++m_numAccesses;
		return doubleToString(m_value);
	}

private:
	static std::string doubleToString(double value);
	static double stringToDouble(std::string_view value);

	double m_value{ 0 };
	mutable unsigned m_numAccesses{ 0 };
};
/*
inline double SpreadsheetCell::getValue() const
{
	++m_numAccesses;
	return m_value;
}

inline std::string SpreadsheetCell::getString() const
{
	++m_numAccesses;
	return doubleToString(m_value);
}
*/