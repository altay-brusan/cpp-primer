/*
 * Chapter 26 - Class Template Partial Specialization
 *
 * A partial specialization of Grid for const char* keys that leaves the WIDTH
 * and HEIGHT non-type parameters free while fixing the element type. The
 * specialization stores std::string cells instead of const char*, so that the
 * grid owns copies of the strings rather than dangling pointers.
 *
 * Key notes:
 *   - The template header lists only the unspecialized parameters
 *     (WIDTH, HEIGHT), but the class name still names all three arguments:
 *     Grid<const char*, WIDTH, HEIGHT>.
 *   - Unlike full specializations, every out-of-class method keeps a template
 *     header.
 */

#pragma once

#include "Grid.h"

template <std::size_t WIDTH, std::size_t HEIGHT>
class Grid<const char*, WIDTH, HEIGHT>
{
public:
	Grid() = default;
	virtual ~Grid() = default;

	// Explicitly default a copy constructor and copy assignment operator.
	Grid(const Grid& src) = default;
	Grid& operator=(const Grid & rhs) = default;

	// Explicitly default a move constructor and move assignment operator.
	Grid(Grid&& src) = default;
	Grid& operator=(Grid&& rhs) = default;

	std::optional<std::string>& at(std::size_t x, std::size_t y);
	const std::optional<std::string>& at(std::size_t x, std::size_t y) const;

	std::size_t getHeight() const { return HEIGHT; }
	std::size_t getWidth() const { return WIDTH; }

private:
	void verifyCoordinate(std::size_t x, std::size_t y) const;

	std::optional<std::string> m_cells[WIDTH][HEIGHT];
};

template <std::size_t WIDTH, std::size_t HEIGHT>
void Grid<const char*, WIDTH, HEIGHT>::verifyCoordinate(std::size_t x, std::size_t y) const
{
	if (x >= WIDTH) {
		throw std::out_of_range{
			std::format("x ({}) must be less than width ({}).", x, WIDTH) };
	}
	if (y >= HEIGHT) {
		throw std::out_of_range{
			std::format("y ({}) must be less than height ({}).", y, HEIGHT) };
	}
}

template <std::size_t WIDTH, std::size_t HEIGHT>
const std::optional<std::string>& Grid<const char*, WIDTH, HEIGHT>::at(std::size_t x, std::size_t y) const
{
	verifyCoordinate(x, y);
	return m_cells[x][y];
}

template <std::size_t WIDTH, std::size_t HEIGHT>
std::optional<std::string>& Grid<const char*, WIDTH, HEIGHT>::at(std::size_t x, std::size_t y)
{
	return const_cast<std::optional<std::string>&>(std::as_const(*this).at(x, y));
}
