/*
 * Chapter 9 - Implementing Move Semantics
 *
 * Implementation for Spreadsheet.h - see the header for the conceptual notes.
 * Each special member function prints which one ran, which makes it easy to watch
 * vector growth and assignment in the driver call the move members instead of copies.
 */
#include "Spreadsheet.h"
#include <print>
#include <stdexcept>
#include <utility>
#include <format>

using namespace std;

Spreadsheet::Spreadsheet(size_t width, size_t height)
	: m_width { width }
	, m_height { height }
{
	println("Normal constructor");

	m_cells = new SpreadsheetCell*[m_width];
	for (size_t i{ 0 }; i < m_width; ++i) {
		m_cells[i] = new SpreadsheetCell[m_height];
	}
}

Spreadsheet::~Spreadsheet()
{
	cleanup();
}

Spreadsheet::Spreadsheet(const Spreadsheet& src)
	: Spreadsheet { src.m_width, src.m_height }
{
	println("Copy constructor");

	// The ctor-initializer of this constructor delegates first to the
	// non-copy constructor to allocate the proper amount of memory.

	// The next step is to copy the data.
	for (size_t i{ 0 }; i < m_width; ++i) {
		for (size_t j{ 0 }; j < m_height; ++j) {
			m_cells[i][j] = src.m_cells[i][j];
		}
	}
}

void Spreadsheet::cleanup() noexcept
{
	for (size_t i{ 0 }; i < m_width; ++i) {
		delete[] m_cells[i];
	}
	delete[] m_cells;
	m_cells = nullptr;
	m_width = m_height = 0;
}

void Spreadsheet::verifyCoordinate(size_t x, size_t y) const
{
	if (x >= m_width) {
		throw out_of_range { format("x ({}) must be less than width ({}).", x, m_width) };
	}
	if (y >= m_height) {
		throw out_of_range { format("y ({}) must be less than height ({}).", y, m_height) };
	}
}

void Spreadsheet::setCellAt(size_t x, size_t y, const SpreadsheetCell& cell)
{
	verifyCoordinate(x, y);
	m_cells[x][y] = cell;
}

SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y)
{
	verifyCoordinate(x, y);
	return m_cells[x][y];
}

void Spreadsheet::swap(Spreadsheet& other) noexcept
{
	std::swap(m_width, other.m_width);
	std::swap(m_height, other.m_height);
	std::swap(m_cells, other.m_cells);
}

void swap(Spreadsheet& first, Spreadsheet& second) noexcept
{
	first.swap(second);
}

Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs)
{
	println("Copy assignment operator");

	// Copy-and-swap idiom
	Spreadsheet temp { rhs }; // Do all the work in a temporary instance
	swap(temp); // Commit the work with only non-throwing operations
	return *this;
}

void Spreadsheet::moveFrom(Spreadsheet& src) noexcept
{
	// Shallow copy of data - just grab the pointer, do not allocate.
	m_width = src.m_width;
	m_height = src.m_height;
	m_cells = src.m_cells;

	// Reset the source object, because ownership has been moved!
	// If we leave src.m_cells pointing at the buffer, src's destructor would
	// delete it out from under us.
	src.m_width = 0;
	src.m_height = 0;
	src.m_cells = nullptr;
}

// Move constructor
Spreadsheet::Spreadsheet(Spreadsheet&& src) noexcept
{
	println("Move constructor");

	moveFrom(src);
}

// Move assignment operator
Spreadsheet& Spreadsheet::operator=(Spreadsheet&& rhs) noexcept
{
	println("Move assignment operator");

	// Guard against `sheet1 = std::move(sheet1);` - without this check, cleanup()
	// would free the very memory we are about to take ownership of.
	if (this == &rhs) {
		return *this;
	}

	// Free the old memory and move ownership
	cleanup();

	moveFrom(rhs);

	return *this;
}
