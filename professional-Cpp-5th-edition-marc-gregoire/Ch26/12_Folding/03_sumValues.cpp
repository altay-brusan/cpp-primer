/*
 * Chapter 26 - Binary Left Fold
 *
 * sumValues() adds all of its arguments using a binary left fold,
 * (init + ... + values), which expands to (((init + v0) + v1) + ...). A binary
 * fold needs an explicit Init operand, so the template takes a leading normal
 * parameter plus a parameter pack and therefore requires at least one argument.
 */

#include <print>

using namespace std;

template<typename T, typename... Values>
auto sumValues(const T& init, const Values&... values)
{
	return (init + ... + values);
}

int main()
{
	println("{}", sumValues(1, 2, 3.3));
	println("{}", sumValues(1));
	//println("{}", sumValues());  // Does not compile!
}
