/*
 * Chapter 12 - Class Templates (first version): Grid<T>
 *
 * The same shape as GameBoard, but parameterized on the cell type T. The
 * book takes you from non-generic to generic by changing the storage
 * (now `vector<optional<T>>`) and adding `template <typename T>` to every
 * declaration.
 *
 * Key notes on templates:
 *   - Class templates are NOT classes. `Grid` alone is the *name of the
 *     template*; `Grid<int>` is a *specialization* - the actual class.
 *   - Template definitions live in the header. The compiler needs to see
 *     the body to instantiate it for whatever T you use. (See the bottom
 *     of GridTest.cpp for explicit instantiation, which is the workaround
 *     when you really want to put bodies in a .cpp.)
 *   - `optional<T>` makes "no value yet" first-class without forcing T to
 *     be default-constructible *or* introducing nullptrs.
 *   - The `at()` pair uses the same as_const + const_cast trick as
 *     GameBoard to share the bounds-check body.
 *   - Five special members default to the right thing (vector + optional
 *     handle their own copies/moves/destruction). You only need to write
 *     them out explicitly when you want to be loud about the choice.
 */
#pragma once

#include <cstddef>
#include <vector>
#include <format>
#include <optional>
#include <stdexcept>
#include <utility>

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

	std::optional<T>& at(std::size_t x, std::size_t y);
	const std::optional<T>& at(std::size_t x, std::size_t y) const;

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
		throw std::out_of_range { std::format("x ({}) must be less than width ({}).", x, m_width) };
	}
	if (y >= m_height) {
		throw std::out_of_range { std::format("y ({}) must be less than height ({}).", y, m_height) };
	}
}

template <typename T>
const std::optional<T>& Grid<T>::at(std::size_t x, std::size_t y) const
{
	verifyCoordinate(x, y);
	return m_cells[x + y * m_width];
}

template <typename T>
std::optional<T>& Grid<T>::at(std::size_t x, std::size_t y)
{
	return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
}
