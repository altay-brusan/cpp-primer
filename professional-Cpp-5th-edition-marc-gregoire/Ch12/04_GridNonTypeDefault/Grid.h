/*
 * Chapter 12 - Default Template Arguments
 *
 * Template parameters can have defaults, just like function parameters.
 * The book extends Grid to default `T = int` and `WIDTH = HEIGHT = 10`.
 * Now you can write `Grid<>` and get a 10x10 int grid.
 *
 * Key notes:
 *   - Once a parameter has a default, every parameter after it must also
 *     have one (same rule as function default arguments).
 *   - You can mix-and-match at the call site: `Grid<int, 5>` keeps the
 *     default HEIGHT of 10.
 *   - Be intentional with defaults. They can mask mistakes - if a caller
 *     forgets to specify HEIGHT, they get 10 silently instead of a
 *     compiler error.
 *   - Default arguments don't have to be literals. Other type names,
 *     `decltype` expressions, and constant expressions referring to other
 *     template parameters are all allowed.
 */
#pragma once

#include <cstddef>
#include <format>
#include <optional>
#include <stdexcept>
#include <utility>

template <typename T = int, std::size_t WIDTH = 10, std::size_t HEIGHT = 10>
class Grid
{
public:
	Grid() = default;
	virtual ~Grid() = default;

	// Explicitly default a copy constructor and copy assignment operator.
	Grid(const Grid& src) = default;
	Grid& operator=(const Grid& rhs) = default;

	// Explicitly default a move constructor and move assignment operator.
	Grid(Grid&& src) = default;
	Grid& operator=(Grid&& rhs) = default;

	std::optional<T>& at(std::size_t x, std::size_t y);
	const std::optional<T>& at(std::size_t x, std::size_t y) const;

	std::size_t getHeight() const { return HEIGHT; }
	std::size_t getWidth() const { return WIDTH; }

private:
	void verifyCoordinate(std::size_t x, std::size_t y) const;

	std::optional<T> m_cells[WIDTH][HEIGHT];
};

template <typename T, std::size_t WIDTH, std::size_t HEIGHT>
void Grid<T, WIDTH, HEIGHT>::verifyCoordinate(std::size_t x, std::size_t y) const
{
	if (x >= WIDTH) {
		throw std::out_of_range { std::format("x ({}) must be less than width ({}).", x, WIDTH) };
	}
	if (y >= HEIGHT) {
		throw std::out_of_range { std::format("y ({}) must be less than height ({}).", y, HEIGHT) };
	}
}

template <typename T, std::size_t WIDTH, std::size_t HEIGHT>
const std::optional<T>& Grid<T, WIDTH, HEIGHT>::at(std::size_t x, std::size_t y) const
{
	verifyCoordinate(x, y);
	return m_cells[x][y];
}

template <typename T, std::size_t WIDTH, std::size_t HEIGHT>
std::optional<T>& Grid<T, WIDTH, HEIGHT>::at(std::size_t x, std::size_t y)
{
	return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
}
