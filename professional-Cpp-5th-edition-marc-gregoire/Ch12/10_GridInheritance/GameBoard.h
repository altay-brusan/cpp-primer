/*
 * Chapter 12 - Inheritance From a Class Template (derived)
 *
 * `GameBoard<T> : public Grid<T>` - a template inheriting from a template.
 * Both classes use the same T, so you can use a GameBoard like a Grid plus
 * a `move()` operation.
 *
 * Two C++ rules show up in this small file:
 *
 *   1. `using Grid<T>::Grid;` - inherit Grid's constructors. Without this
 *      line, GameBoard would only have the implicit default ctor.
 *
 *   2. Inside member functions, `at()` is NOT looked up in the base class
 *      automatically. C++ calls this "dependent name lookup": the
 *      compiler can't be sure Grid<T> *has* an `at` (some specialization
 *      could remove it), so you must qualify the call with either
 *      `Grid<T>::at(...)` or `this->at(...)`. Both are shown.
 *
 * Key notes:
 *   - The dependent-name lookup rule is one of the most surprising parts
 *     of templates. If you forget the qualifier and get an error like
 *     "no member named at in GameBoard", reach for `this->at` first.
 *   - Inheritance from a class template is a normal IS-A relationship -
 *     a GameBoard<ChessPiece> can be passed where a Grid<ChessPiece>& is
 *     expected.
 */
#pragma	once

#include "Grid.h"

template <typename T>
class GameBoard : public Grid<T>
{
public:
	// Inherit constructors from Grid<T>.
	using Grid<T>::Grid;

	void move(std::size_t xSrc, std::size_t ySrc, std::size_t xDest, std::size_t yDest);
};

template <typename T>
void GameBoard<T>::move(std::size_t xSrc, std::size_t ySrc, std::size_t xDest, std::size_t yDest)
{
	Grid<T>::at(xDest, yDest) = std::move(Grid<T>::at(xSrc, ySrc));
	Grid<T>::at(xSrc, ySrc).reset(); // Reset source cell
	// Or:
	// this->at(xDest, yDest) = std::move(this->at(xSrc, ySrc));
	// this->at(xSrc, ySrc).reset();
}
