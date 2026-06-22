/*
 * Chapter 15 - Multidimensional Subscripting Operator
 *
 * A 2D Grid template that overloads the C++23 multi-argument subscripting operator,
 * operator[](size_t x, size_t y), so cells can be accessed as grid[x, y]. Elements are
 * stored in a flat std::vector<std::optional<T>> and addressed as x + y * width. A const
 * and a non-const overload are provided; the non-const one delegates to the const one via
 * std::as_const and const_cast to avoid duplicating the bounds-checking logic.
 *
 * Key notes:
 *   - Before C++23 a single index was the only option; here operator[] takes two indices,
 *     removing the need for the function call operator to do multidimensional access.
 */
#pragma once

#include <cstddef>
#include <vector>
#include <optional>
#include <stdexcept>
#include <utility>
#include <format>

template <typename T>
class Grid
{
public:
	explicit Grid(std::size_t width = DefaultWidth, std::size_t height = DefaultHeight);
	virtual ~Grid() = default;

	// Explicitly default a copy constructor and copy assignment operator.
	Grid(const Grid& src) = default;
	Grid& operator=(const Grid& rhs) = default;

	// Explicitly default a move constructor and move assignment operator.
	Grid(Grid&& src) = default;
	Grid& operator=(Grid&& rhs) = default;

	std::optional<T>& operator[](std::size_t x, std::size_t y);
	const std::optional<T>& operator[](std::size_t x, std::size_t y) const;

	std::size_t getHeight() const { return m_height; }
	std::size_t getWidth() const { return m_width; }

	static constexpr std::size_t DefaultWidth{ 10 };
	static constexpr std::size_t DefaultHeight{ 10 };

private:
	void verifyCoordinate(std::size_t x, std::size_t y) const;

	std::vector<std::optional<T>> m_cells;
	std::size_t m_width { 0 }, m_height { 0 };
};

template <typename T>
Grid<T>::Grid(std::size_t width, std::size_t height)
	: m_width{ width }
	, m_height{ height }
{
	m_cells.resize(m_width * m_height);
}

template <typename T>
void Grid<T>::verifyCoordinate(std::size_t x, std::size_t y) const
{
	if (x >= m_width) {
		throw std::out_of_range {
			std::format("x ({}) must be less than width ({}).", x, m_width) };
	}
	if (y >= m_height) {
		throw std::out_of_range {
			std::format("y ({}) must be less than height ({}).", y, m_height) };
	}
}

template <typename T>
const std::optional<T>& Grid<T>::operator[](std::size_t x, std::size_t y) const
{
	verifyCoordinate(x, y);
	return m_cells[x + y * m_width];
}

template <typename T>
std::optional<T>& Grid<T>::operator[](std::size_t x, std::size_t y)
{
	return const_cast<std::optional<T>&>(std::as_const(*this)[x, y]);
}
