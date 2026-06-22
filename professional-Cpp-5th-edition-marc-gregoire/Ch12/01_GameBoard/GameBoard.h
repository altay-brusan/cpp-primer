/*
 * Chapter 12 - Templates (kickoff): The GameBoard Class
 *
 * Before introducing templates, the book builds a *non-generic* GameBoard
 * that stores `unique_ptr<GamePiece>` cells. The next sample (02_Grid) turns
 * this same shape into a class template parameterized on the cell type T.
 *
 * The class brings together a handful of techniques you've now seen:
 *   - Polymorphic cells via the abstract `GamePiece` base + `clone()`
 *     (so the copy ctor can deep-copy heterogenous derived pieces).
 *   - Value-semantic ownership via `vector<unique_ptr<GamePiece>>` - the
 *     vector owns the slots, each unique_ptr owns one piece (or nullptr).
 *   - Copy-and-swap idiom for the assignment operator (Ch 09).
 *   - `noexcept` swap as the commit step.
 *   - Default move ctor / move assignment - vector and unique_ptr are
 *     move-friendly, so the defaults are correct and fast.
 *   - `static constexpr` defaults for the board size.
 *   - `const`-overloaded `at()` and the `const_cast(as_const(...))` trick
 *     to avoid duplicating the body in the non-const version.
 *
 * Once you've internalized this layout, the leap to a template in the
 * next sample is mostly just changing `unique_ptr<GamePiece>` to `T`.
 */
#pragma once

#include <memory>
#include <cstddef>
#include <vector>

class GamePiece
{
public:
	virtual ~GamePiece() = default;
	virtual std::unique_ptr<GamePiece> clone() const = 0;
};

class GameBoard
{
public:
	explicit GameBoard(std::size_t width = DefaultWidth, std::size_t height = DefaultHeight);
	GameBoard(const GameBoard& src);   // copy constructor
	virtual ~GameBoard() = default;    // virtual defaulted destructor
	GameBoard& operator=(const GameBoard& rhs); // assignment operator
	
	// Explicitly default a move constructor and move assignment operator.
	GameBoard(GameBoard&& src) = default;
	GameBoard& operator=(GameBoard&& src) = default;

	std::unique_ptr<GamePiece>& at(std::size_t x, std::size_t y);
	const std::unique_ptr<GamePiece>& at(std::size_t x, std::size_t y) const;

	std::size_t getHeight() const { return m_height; }
	std::size_t getWidth() const { return m_width; }

	static constexpr std::size_t DefaultWidth{ 10 };
	static constexpr std::size_t DefaultHeight{ 10 };

	void swap(GameBoard& other) noexcept;

private:
	void verifyCoordinate(std::size_t x, std::size_t y) const;

	std::vector<std::unique_ptr<GamePiece>> m_cells;
	std::size_t m_width { 0 }, m_height { 0 };
};

void swap(GameBoard& first, GameBoard& second) noexcept;
