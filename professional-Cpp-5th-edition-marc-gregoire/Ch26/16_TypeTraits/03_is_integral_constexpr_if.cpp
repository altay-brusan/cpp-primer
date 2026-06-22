/*
 * Chapter 26 - Replacing Tag Dispatch with constexpr if
 *
 * The same integral-vs-non-integral message, now in a single process()
 * function template using if constexpr (is_integral_v<T>). This removes the
 * need for the separate helper overloads of the previous sample.
 */

#include <print>
#include <type_traits>
#include <string>

using namespace std;

template<typename T>
void process(const T& t)
{
	if constexpr (is_integral_v<T>) {
		println("{} is an integral type.", t);
	} else {
		println("{} is a non-integral type.", t);
	}
}

int main()
{
	process(123);
	process(2.2);
	process("Test"s);
}
