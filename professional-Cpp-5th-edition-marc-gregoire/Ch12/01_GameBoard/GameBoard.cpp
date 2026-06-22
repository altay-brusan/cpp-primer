/*
 * Chapter 12 - GameBoard (implementation)
 *
 * Bodies for the non-template GameBoard. Highlights worth noting:
 *   - Copy ctor delegates to the sizing ctor first, then clones each piece.
 *     Cloning is the only way to deep-copy through a `unique_ptr<GamePiece>`
 *     because the dynamic type isn't statically known.
 *   - `at()` const+non-const pair: the non-const version forwards to the
 *     const one via `as_const(*this)` + `const_cast`. That avoids
 *     duplicating the bounds-check body.
 *   - Both swap functions are `noexcept`; the member version is what the
 *     non-member swap and the copy-and-swap idiom rely on.
 */
#include "GameBoard.h"
#include <stdexcept>
#include <utility>
#include <format>

using namespace std;

GameBoard::GameBoard(size_t width, size_t height)
	: m_width{ width }
	, m_height{ height }
{
	m_cells.resize(m_width * m_height);
}

GameBoard::GameBoard(const GameBoard& src)
	: GameBoard{ src.m_width, src.m_height }
{
	// The ctor-initializer of this constructor delegates first to the
	// non-copy constructor to allocate the proper amount of memory.

	// The next step is to copy the data.
	for (size_t i{ 0 }; i < m_cells.size(); ++i) {
		if (src.m_cells[i]) {
			m_cells[i] = src.m_cells[i]->clone();
		}
	}
}

void GameBoard::verifyCoordinate(size_t x, size_t y) const
{
	if (x >= m_width) {
		throw out_of_range { format("x ({}) must be less than width ({}).", x, m_width) };
	}
	if (y >= m_height) {
		throw out_of_range { format("y ({}) must be less than height ({}).", y, m_height) };
	}
}

void GameBoard::swap(GameBoard& other) noexcept
{
	std::swap(m_width, other.m_width);
	std::swap(m_height, other.m_height);
	std::swap(m_cells, other.m_cells);
}

void swap(GameBoard& first, GameBoard& second) noexcept
{
	first.swap(second);
}

GameBoard& GameBoard::operator=(const GameBoard& rhs)
{
	// Copy-and-swap idiom
	GameBoard temp{ rhs }; // Do all the work in a temporary instance
	swap(temp);   // Commit the work with only non-throwing operations
	return *this;
}

const unique_ptr<GamePiece>& GameBoard::at(size_t x, size_t y) const
{
	verifyCoordinate(x, y);
	return m_cells[x + y * m_width];
}

unique_ptr<GamePiece>& GameBoard::at(size_t x, size_t y)
{
	return const_cast<unique_ptr<GamePiece>&>(as_const(*this).at(x, y));
}
