/*
 * Chapter 19 - Binding Arguments with std::bind
 *
 * Demonstrates std::bind as an adapter that fixes or reorders a callable's arguments.
 * f1 binds func()'s second argument to a fixed string and exposes the first via the
 * placeholder _1, so it can be called with just an int. f2 uses placeholders _2 and _1 to
 * swap the argument order. The placeholders live in the std::placeholders namespace.
 *
 * Key notes:
 *   - bind()'s return type is unspecified, hence auto.
 *   - The book recommends lambda expressions over bind() for readability.
 */
#include <print>
#include <functional>

using namespace std;

void func(int num, string_view str)
{
	println("func({}, {})", num, str);
}

int main()
{
	// Bind second argument to a fixed value.
	string myString{ "abc" };
	auto f1{ bind(func, placeholders::_1, myString) };
	f1(16);

	// Rearrange arguments
	auto f2{ bind(func, placeholders::_2, placeholders::_1) };
	f2("Test", 32);
}

