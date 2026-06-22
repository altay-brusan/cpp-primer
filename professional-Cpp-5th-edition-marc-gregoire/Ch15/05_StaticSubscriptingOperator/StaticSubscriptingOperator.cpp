/*
 * Chapter 15 - Static Subscripting Operator
 *
 * Demonstrates a static operator[] (C++23). FigureEnumToString overloads
 * static constexpr operator[](Figure) to map a Figure enumerator to its name as a
 * string_view. Because the operator is static and holds no state, it can be invoked
 * either through an instance (converter[f]) or on a temporary (FigureEnumToString{}[f]).
 */
#include <print>
#include <string_view>

using namespace std;

enum class Figure { Diamond, Heart, Spade, Club };

class FigureEnumToString
{
public:
	static constexpr string_view operator[](Figure figure) noexcept
	{
		switch (figure) {
		case Figure::Diamond: return "Diamond";
		case Figure::Heart: return "Heart";
		case Figure::Spade: return "Spade";
		case Figure::Club: return "Club";
		}
	}
};

int main()
{
	Figure f{ Figure::Spade };
	FigureEnumToString converter;
	println("{}", converter[f]);
	println("{}", FigureEnumToString{}[f]);
}
