/*
 * Chapter 12 - Non-Type Template Parameters
 *
 * Template parameters don't have to be types. They can also be integral
 * values, enum values, pointers/references with linkage, `auto`-deduced
 * values, or other things known at compile time.
 *
 * Here `Grid<T, WIDTH, HEIGHT>` takes two `size_t` non-type parameters.
 * Because the dimensions are part of the type:
 *   - The storage can be a built-in 2D array, no vector allocation needed.
 *   - The compiler can prove certain bounds at compile time.
 *   - Each (W, H) combination is a SEPARATE TYPE - `Grid<int, 10, 10>` is
 *     not assignable from `Grid<int, 11, 10>`.
 *
 * Key notes:
 *   - The arguments must be *constant expressions* at the call site. The
 *     driver shows the variations: literal `10`, a `const size_t` variable,
 *     a `constexpr` function call.
 *   - This was always allowed for integral types; C++20 widened it to
 *     `auto` non-type parameters and structural class types.
 *   - 04_GridNonTypeDefault adds default values for these parameters.
 */
#pragma once

#include <cstddef>
#include <format>
#include <optional>
#include <stdexcept>
#include <utility>

template <typename T, std::size_t WIDTH, std::size_t HEIGHT>
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
