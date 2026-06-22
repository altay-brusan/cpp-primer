/*
 * Chapter 19 - bind_front and bind_back
 *
 * Demonstrates the simpler binders std::bind_front (C++20) and std::bind_back (C++23),
 * which bind leading or trailing arguments without needing placeholders. bind_front(func,
 * 42) fixes the first argument, so f5 is called with only the remaining string. bind_back(
 * func, "Hello") fixes the last argument, so f6 is called with only the leading int.
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
	auto f5{ bind_front(func, 42) };
	f5("Hello");

	auto f6{ bind_back(func, "Hello") };
	f6(42);
}
