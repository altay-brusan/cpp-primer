/*
 * Chapter 12 - Deducing the Function Return Type Four Ways
 *
 * Adding two values of different types - what does the function return?
 * Four equivalent (or near-equivalent) ways to express it, all preserved
 * in this file for comparison.
 *
 *   1. `auto add(...)` - the modern choice. Return type deduced from the
 *      return statement. Loses references/cv-qualifiers like a regular
 *      auto variable would.
 *
 *   2. `decltype(auto) add(...)` - same idea, but preserves references
 *      and cv-qualifiers. Use when the body returns `*ptr` or a member
 *      and you need to keep the reference.
 *
 *   3. `auto add(...) -> decltype(t1 + t2)` - trailing return type with
 *      decltype on the parameters. Works back to C++11; useful when you
 *      need to talk about the return type in terms of the parameters.
 *
 *   4. `decltype(declval<T1>() + declval<T2>()) add(...)` - the most
 *      verbose form. `std::declval<X>()` is a "fake X for type
 *      computation" - only usable inside decltype/sizeof contexts where
 *      no object is actually evaluated. Useful when X is not
 *      default-constructible.
 *
 * Default to option 1. Reach for 2 if you need reference preservation,
 * 3 if you're stuck on a pre-C++14 compiler, and 4 in template
 * metaprogramming where you don't actually have a value to take decltype of.
 */
#include <print>

// using automatic function return type deduction
template<typename T1, typename T2>
auto add(const T1& t1, const T2& t2)
{
	return t1 + t2;
}

// using decltype(auto)
//template<typename T1, typename T2>
//decltype(auto) add(const T1& t1, const T2& t2)
//{
//	return t1 + t2;
//}

// Using the alternative function syntax
//template<typename T1, typename T2>
//auto add(const T1& t1, const T2& t2) -> decltype(t1 + t2)
//{
//	return t1 + t2;
//}

// Using std::declval<>()
//template<typename T1, typename T2>
//decltype(std::declval<T1>() + std::declval<T2>()) add(const T1& t1, const T2& t2)
//{
//	return t1 + t2;
//}

int main()
{
	std::println("{}", add(2, 4));
}
