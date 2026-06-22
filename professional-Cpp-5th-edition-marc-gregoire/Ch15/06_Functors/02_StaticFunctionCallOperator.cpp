/*
 * Chapter 15 - Static Function Call Operator
 *
 * Shows the C++23 static operator(). Because Squarer's function call operator keeps no
 * per-object state, it is declared static constexpr, letting it be invoked directly as
 * Squarer::operator()(x) or on a temporary Squarer{}(x) with no instance required.
 */
#include <print>

using namespace std;

class Squarer
{
public:
	static constexpr int operator()(int value) noexcept
	{
		return value * value;
	}
};

int main()
{
	int x{ 3 };

	int xSquared{ Squarer::operator()(x) };
	int xSquaredAgain{ Squarer{}(xSquared) };

	println("{} squared is {}, and squared again is {}.", x, xSquared, xSquaredAgain);
}
