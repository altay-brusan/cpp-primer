/*
 * Chapter 24 - std::apply
 *
 * Demonstrates std::apply(), which calls a given callable (function, lambda, or
 * function object) by unpacking the elements of a tuple and passing them as the
 * call's arguments. Here the two-element tuple { 39, 3 } is spread into the add()
 * function's two parameters. Like make_from_tuple(), apply() is most valuable in
 * generic, template-based code.
 */

#include <print>
#include <tuple>
#include <functional>

using namespace std;

int add(int a, int b)
{
	return a + b;
}

int main()
{
	println("{}", apply(add, tuple{ 39, 3 }));
}