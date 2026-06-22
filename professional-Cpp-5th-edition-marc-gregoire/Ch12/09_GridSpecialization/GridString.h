/*
 * Chapter 12 - Template Specialization (the const char* override)
 *
 * `template <>` followed by `class Grid<const char*>` declares a *full
 * specialization*. The empty `<>` means "I'm specializing every parameter
 * of the primary template" - in this case the only one, T.
 *
 * Why specialize?
 *   - The primary template would store `optional<const char*>`, leaving
 *     the grid pointing at user-owned data. If those pointers dangle, you
 *     read garbage.
 *   - The specialization stores `optional<std::string>` instead. Now the
 *     grid OWNS its strings and is safe across copy/move/lifetime.
 *
 * Key notes:
 *   - A full specialization is a totally separate class definition. It
 *     does NOT inherit anything from the primary template - members,
 *     bases, helpers, all must be re-declared.
 *   - The compiler picks the specialization automatically when you
 *     instantiate the template with `T = const char*`.
 *   - Compare with *partial* specialization (e.g. `Grid<T*>`), which the
 *     book covers later. Full specialization fixes every parameter;
 *     partial fixes some pattern.
 */
#pragma once

#include "Grid.h"
#include <string>

template <>
class Grid<const char*>
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

	std::optional<std::string>& at(std::size_t x, std::size_t y);
	const std::optional<std::string>& at(std::size_t x, std::size_t y) const;

	std::size_t getHeight() const { return m_height; }
	std::size_t getWidth() const { return m_width; }

	static constexpr std::size_t DefaultWidth{ 10 };
	static constexpr std::size_t DefaultHeight{ 10 };

private:
	void verifyCoordinate(std::size_t x, std::size_t y) const;

	std::vector<std::optional<std::string>> m_cells;
	std::size_t m_width { 0 }, m_height { 0 };
};
