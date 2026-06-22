/*
 * Chapter 12 - Inheritance From a Class Template: driver
 *
 * Note: this `ChessPiece` is just an empty class - we're not exercising
 * any of the polymorphism story from earlier samples, only the storage
 * and `move()` mechanics on the GameBoard.
 */
#include "GameBoard.h"

using namespace std;

class ChessPiece
{
};

int main()
{
	GameBoard<ChessPiece> chessBoard{ 8, 8 };

	ChessPiece pawn;
	chessBoard.at(0, 0) = pawn;
	chessBoard.move(0, 0, 0, 1);
}
