/*
 * Chapter 26 - Unary Right Fold over the Comma Operator
 *
 * printValues() writes every argument in its parameter pack to the console
 * using a unary right fold (println("{}", values), ...). The comma fold turns
 * the pack into a sequence of print statements regardless of how many or what
 * types of arguments are passed.
 */

#include <print>

using namespace std;

template<typename... Values>
void printValues(const Values&... values)
{
	(println("{}", values), ...);
}

int main()
{
	printValues(1, "test", 2.34);
}