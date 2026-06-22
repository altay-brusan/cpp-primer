/*
 * Chapter 26 - Template Recursion for an N-Dimensional Grid
 *
 * Implements a real N-dimensional grid with NDGrid<T, N>, where the element
 * type is recursively another NDGrid<T, N-1>. A partial specialization
 * NDGrid<T, 1> is the base case whose element type is finally T itself. This is
 * template recursion: each dimension is a vector of grids of one lower
 * dimension.
 *
 * Key notes:
 *   - resize() must explicitly resize each nested subgrid, because the vector
 *     creates its elements with the default (zero-argument) constructor.
 *   - operator[] returns NDGrid<T, N-1>&, peeling off one dimension per index.
 */

#pragma once

#include <vector>
#include <cstddef>

template <typename T, std::size_t N>
class NDGrid final
{
public:
	explicit NDGrid(std::size_t size = DefaultSize) { resize(size); }

	NDGrid<T, N-1>& operator[](std::size_t x) { return m_elements[x]; }
	const NDGrid<T, N-1>& operator[](std::size_t x) const { return m_elements[x]; }

	void resize(std::size_t newSize)
	{
		m_elements.resize(newSize, NDGrid<T, N-1> { newSize });
	}

	std::size_t getSize() const { return m_elements.size(); }

	static constexpr std::size_t DefaultSize{ 10 };

private:
	std::vector<NDGrid<T, N-1>> m_elements;
};

template <typename T>
class NDGrid<T, 1> final
{
public:
	explicit NDGrid(std::size_t size = DefaultSize) { resize(size); }

	T& operator[](std::size_t x) { return m_elements[x]; }
	const T& operator[](std::size_t x) const { return m_elements[x]; }

	void resize(std::size_t newSize) { m_elements.resize(newSize); }
	std::size_t getSize() const { return m_elements.size(); }

	static constexpr std::size_t DefaultSize{ 10 };

private:
	std::vector<T> m_elements;
};
