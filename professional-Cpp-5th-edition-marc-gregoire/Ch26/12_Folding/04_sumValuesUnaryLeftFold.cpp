/*
 * Chapter 26 - Unary Left Fold
 *
 * sumValues() implemented as a unary left fold (... + values), which needs no
 * explicit Init operand. Because a non-comma/non-logical unary fold has no
 * identity element, this version still requires at least one argument to be
 * supplied.
 */

#include <print>

using namespace std;

template<typename... Values>
auto sumValues(const Values&... values)
{
	return (... + values);
}

int main()
{
	println("{}", sumValues(1, 2, 3.3));
	println("{}", sumValues(1));
	//println("{}", sumValues());  // Does not compile!
}
