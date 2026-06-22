/*
 * Chapter 26 - Static Assertions
 *
 * static_assert checks a condition at compile time and aborts compilation with a
 * message if it is false. A namespace-scope assertion here requires a 64-bit
 * build, and foo() combines static_assert with the is_integral_v trait to reject
 * non-integral arguments.
 *
 * Key notes:
 *   - The message argument is optional since C++17.
 *   - The book recommends C++20 concepts over static_assert-with-traits for
 *     constraining template arguments.
 */

#include <print>
#include <type_traits>

using namespace std;

static_assert(sizeof(void*) == 8, "Requires 64-bit compilation.");

// Using static_assert() and type traits:
template <typename T>
void foo(const T& /*t*/)
{
	static_assert(is_integral_v<T>, "T must be an integral type.");
}

int main()
{
	foo(123);
	//foo(1.2);
}