/*
 * Chapter 12 - Friend Function Templates
 *
 * `operator+` for `Grid<T>` is a non-member function template - it has to
 * be a non-member so each Grid can be on either side of `+`. But the body
 * needs to read `m_width`, `m_height`, etc. directly, so the function has
 * to be a *friend* of the class.
 *
 * The line that does it:
 *
 *     friend Grid operator+<T>(const Grid& lhs, const Grid& rhs);
 *
 * Read it as: "this Grid is a friend of the operator+ template
 * instantiation for the current T". The `<T>` is critical - without it,
 * the compiler would befriend a non-template `operator+`, which doesn't
 * exist.
 *
 * Some compilers (clang, recent gcc) want a forward declaration of the
 * operator+ template BEFORE the class so they know it's a template when
 * the friend line is parsed. If you hit a "no template" error, add this
 * pair of forward declarations above the class:
 *
 *     template <typename T> class Grid;
 *     template <typename T> Grid<T> operator+(const Grid<T>&, const Grid<T>&);
 *
 * MSVC traditionally lets you get away without them.
 */
#pragma once

#include <cstddef>
#include <vector>
#include <format>
#include <optional>
#include <stdexcept>
#include <utility>

// Forward declarations so `friend operator+<T>` inside the class works
// even on strict compilers (clang/gcc).
template <typename T> class Grid;
template <typename T> Grid<T> operator+(const Grid<T>& lhs, const Grid<T>& rhs);

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

	friend Grid operator+<T>(const Grid& lhs, const Grid& rhs);

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

template <typename T>
Grid<T> operator+(const Grid<T>& lhs, const Grid<T>& rhs)
{
	std::size_t minWidth{ std::min(lhs.m_width, rhs.m_width) };
	std::size_t minHeight{ std::min(lhs.m_height, rhs.m_height) };

	Grid<T> result{ minWidth, minHeight };
	for (std::size_t y{ 0 }; y < minHeight; ++y) {
		for (std::size_t x{ 0 }; x < minWidth; ++x) {
			const auto& leftElement{ lhs.at(x, y) };
			const auto& rightElement{ rhs.at(x, y) };
			if (leftElement.has_value() && rightElement.has_value()) {
				result.at(x, y) = leftElement.value() + rightElement.value();
			}
		}
	}

	return result;
}
