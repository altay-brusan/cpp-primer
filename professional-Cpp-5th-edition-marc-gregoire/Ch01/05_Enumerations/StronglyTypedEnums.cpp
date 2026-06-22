/*
 * Chapter 1 - Enumerated Types
 *
 * "enum class" is a strongly typed enumeration: enumerators are scoped to the type and there
 * is no implicit conversion to or from int. That kills two old C bugs - assigning a stray
 * integer to an enum variable, and accidentally comparing enums of different types. Reach
 * each enumerator through its scope, e.g. PieceType::King.
 *
 * Key notes:
 *   - Underlying values: the first enumerator defaults to 0 and each unassigned one is the
 *     previous value + 1. Here King = 1, Queen = 2, Rook = 10, Pawn = 11.
 *   - Pick the underlying type explicitly: "enum class PieceType : unsigned long { ... };".
 *   - Different enum classes can share enumerator names (State::Unknown and Error::Unknown
 *     do not collide). With plain "enum", they would clash.
 *   - To get the integer behind a value: std::to_underlying(piece) (C++23) or
 *     static_cast<std::underlying_type_t<PieceType>>(piece).
 *   - C++20 lets you skip qualification: "using enum PieceType;" brings all enumerators into
 *     scope, or "using PieceType::King;" brings just one. Keep that scope tight to avoid
 *     re-introducing name clashes.
 *   - Plain "enum" (no class) still exists for legacy code; the enumerators leak into the
 *     surrounding scope and convert freely to int. Prefer enum class in new code.
 */

#include <utility>

using namespace std;

enum class PieceType
{
	King = 1,
	Queen,
	Rook = 10,
	Pawn
};

int main()
{
	{
		PieceType piece{ PieceType::King };

		auto underlyingValue{ to_underlying(piece) };
	}

	{
		using enum PieceType;
		PieceType piece{ King };
	}

	{
		using PieceType::King;
		PieceType piece{ King };
		piece = PieceType::Queen;
	}
}
