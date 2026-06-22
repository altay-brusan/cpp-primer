/*
 * Chapter 26 - Logical Operator Traits
 *
 * Demonstrates conjunction, disjunction, and negation, the traits that combine
 * other type traits with logical AND, OR, and NOT. Using their _v variable
 * templates, this prints the boolean results of combining several is_integral
 * checks.
 */

#include <print>
#include <type_traits>

using namespace std;

int main()
{
	print("{} ", conjunction_v<is_integral<int>, is_integral<short>>);
	print("{} ", conjunction_v<is_integral<int>, is_integral<double>>);

	print("{} ", disjunction_v<is_integral<int>, is_integral<double>, is_integral<short>>);

	print("{} ", negation_v<is_integral<int>>);
}
