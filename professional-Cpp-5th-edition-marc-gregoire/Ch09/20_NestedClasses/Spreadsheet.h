/*
 * Chapter 9 - Nested Classes
 *
 * A class can be defined inside another class. Here `SpreadsheetCell` from the
 * previous folders is renamed `Cell` and tucked entirely inside `Spreadsheet`.
 * The nested type lives in the enclosing class's scope, so outside code refers
 * to it as `Spreadsheet::Cell`.
 *
 * Key notes:
 *   - The nested class is a separate type with its own member functions and data;
 *     it does not get an implicit pointer to the enclosing object.
 *   - A nested class has access to the enclosing class's private and protected
 *     members. The enclosing class only has access to the nested class's
 *     public members - unless it is declared a friend.
 *   - Out-of-class definitions for member functions of the nested class use the
 *     full qualified name, e.g. `Spreadsheet::Cell::Cell(double initialValue)`.
 *   - Return TYPES of the outer class's member functions need the qualified name
 *     too: `Spreadsheet::Cell& Spreadsheet::getCellAt(...)`. Parameter types do
 *     not (lookup happens inside the class scope).
 *   - Defining the nested class fully inside the outer class makes the outer
 *     class definition long; folder 21 shows the forward-declared alternative.
 */
#pragma once

#include "Spreadsheet.h"
#include <cstddef>
#include <string>
#include <string_view>

class SpreadsheetApplication { };

class Spreadsheet
{
public:

	class Cell
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
