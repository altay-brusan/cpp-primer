/*
 * Chapter 9 - Nested Classes (forward-declared alternative)
 *
 * Same final type as folder 20, but the body of `Cell` is moved out of the
 * Spreadsheet class. Inside Spreadsheet we keep only `class Cell;` as a forward
 * declaration; the full definition follows below, written as `class
 * Spreadsheet::Cell { ... };`.
 *
 * Key notes:
 *   - Forward-declaring shrinks the Spreadsheet class definition - useful when the
 *     nested class is large.
 *   - The forward declaration alone is enough to declare members of type `Cell&`
 *     and `Cell*`, including arrays of pointers like `Cell** m_cells`.
 *   - You still cannot define a member function that uses Cell by value until the
 *     full `class Spreadsheet::Cell { ... }` is visible.
 *   - The two styles (folders 20 and 21) are interchangeable; pick whichever reads
 *     better for the size of the nested class.
 */
#pragma once


#include <cstddef>
#include <string>
#include <string_view>

class SpreadsheetApplication { };

class Spreadsheet
{
public:
	class Cell;

	Spreadsheet(std::size_t width, std::size_t height,
		const SpreadsheetApplication& theApp);
	Spreadsheet(const Spreadsheet& src);
	~Spreadsheet();
	Spreadsheet& operator=(const Spreadsheet& rhs);

	void setCellAt(std::size_t x, std::size_t y, const Cell& cell);
	Cell& getCellAt(std::size_t x, std::size_t y);
	const Cell& getCellAt(std::size_t x, std::size_t y) const;

	std::size_t getId() const;

	void swap(Spreadsheet& other) noexcept;

	static constexpr std::size_t MaxHeight{ 100 };
	static constexpr std::size_t MaxWidth{ 100 };

private:
	void verifyCoordinate(std::size_t x, std::size_t y) const;

	std::size_t m_id{ 0 };
	std::size_t m_width{ 0 };
	std::size_t m_height{ 0 };
	Cell** m_cells{ nullptr };

	const SpreadsheetApplication& m_theApp;

	static inline std::size_t ms_counter{ 0 };
};

void swap(Spreadsheet& first, Spreadsheet& second) noexcept;

class Spreadsheet::Cell
{
public:
	Cell() = default;
	Cell(double initialValue);
	Cell(std::string_view initialValue);

	void set(double value);
	void set(std::string_view value);

	double getValue() const;
	std::string getString() const;

private:
	std::string doubleToString(double value) const;
	double stringToDouble(std::string_view value) const;

	double m_value{ 0 };
};
