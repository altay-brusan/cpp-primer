/*
 * Chapter 12 - GameBoard (driver)
 *
 * Demonstrates the non-generic GameBoard with a concrete `ChessPiece`. Two
 * things to notice:
 *   - `ChessPiece::clone()` is a one-liner: `make_unique<ChessPiece>(*this)`.
 *     The class doesn't need anything else to participate in the
 *     deep-copy story - the rest is in GameBoard's copy ctor.
 *   - The commented `board.at(1, 2) = ...` line at the bottom of
 *     processGameBoard would fail to compile: `board` is `const`, so `at`
 *     returns the const overload (`const unique_ptr<...>&`), which can't
 *     be assigned to.
 */
#include "GameBoard.h"
#include <memory>
#include <utility>

class ChessPiece : public GamePiece
{
public:
	std::unique_ptr<GamePiece> clone() const override
	{
		// Call the copy constructor to copy this instance
		return std::make_unique<ChessPiece>(*this);
	}
};

void processGameBoard(const GameBoard& board)
{
	const std::unique_ptr<GamePiece>& pawn{ board.at(0, 0) };

	// Doesn't compile
	//board.at(1, 2) = std::make_unique<ChessPiece>();
}

int main()
{
	GameBoard chessBoard{ 8, 8 };
	auto pawn{ std::make_unique<ChessPiece>() };
	chessBoard.at(0, 0) = std::move(pawn);
	chessBoard.at(0, 1) = std::make_unique<ChessPiece>();
	chessBoard.at(0, 1) = nullptr;

	GameBoard board2;
	board2 = chessBoard;

	processGameBoard(board2);
}
