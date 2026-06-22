/*
 * Chapter 12 - Abbreviated Function Template Syntax (C++20)
 *
 * Since C++20, you can use `auto` directly in a function parameter list.
 * Each `auto` parameter is shorthand for an unnamed template parameter:
 *
 *     decltype(auto) add(const auto& t1, const auto& t2) { ... }
 *
 * Is equivalent to:
 *
 *     template <typename T1, typename T2>
 *     decltype(auto) add(const T1& t1, const T2& t2) { ... }
 *
 * Each `auto` introduces a *separate* template parameter, so `add(int, double)`
 * is fine. If you want both parameters to be the *same* type, you still
 * need the long form (or a `requires` clause / concept).
 *
 * Key notes:
 *   - The function still IS a template - it just has implicit parameter names.
 *   - Combine freely with explicit template parameters: a function can have
 *     a `template <typename U>` head AND `auto` parameters.
 *   - Concepts work here too: `void f(std::integral auto x)` constrains the
 *     deduced type to satisfy `std::integral`.
 */
#include <print>

decltype(auto) add(const auto& t1, const auto& t2)
{
	return t1 + t2;
}

int main()
{
	std::println("{}", add(2, 4));
}
