/*
 * Chapter 26 - Building Multidimensional Grids by Nesting
 *
 * A one-dimensional grid template. Because its element type T is arbitrary, you
 * can build higher dimensions by nesting it, e.g. OneDGrid<OneDGrid<int>> for a
 * 2-D grid. This motivates the cleaner template-recursion approach in the next
 * sample (NDGrid).
 *
 * Key notes:
 *   - Like vector, operator[] performs no bounds checking.
 *   - Nesting works but the resulting declarations are verbose and awkward.
 */

#pragma once

#include <vector>
#include <cstddef>

template <typename T>
class OneDGrid final
{
public:
	explicit OneDGrid(std::size_t size = DefaultSize) { resize(size); }

	T& operator[](std::size_t x) { return m_elements[x]; }
	const T& operator[](std::size_t x) const { return m_elements[x]; }

	void resize(std::size_t newSize) { m_elements.resize(newSize); }
	std::size_t getSize() const { return m_elements.size(); }

	static constexpr std::size_t DefaultSize{ 10 };

private:
	std::vector<T> m_elements;
};
