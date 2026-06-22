/*
 * Chapter 26 - Tag Dispatch with true_type / false_type
 *
 * Selects between overloads based on a type trait. process() forwards to one of
 * two processHelper() overloads, passing an instance of is_integral<T> which
 * inherits from either true_type or false_type. Overload resolution then picks
 * the correct helper at compile time.
 *
 * Key notes:
 *   - The trait instance is a tag used only for overload selection, so the
 *     helper parameters are unnamed.
 */

#include <print>
#include <type_traits>
#include <string>

using namespace std;

template <typename T>
void processHelper(const T& t, true_type)
{
	println("{} is an integral type.", t);
}

template <typename T>
void processHelper(const T& t, false_type)
{
	println("{} is a non-integral type.", t);
}

template <typename T>
void process(const T& t)
{
	processHelper(t, is_integral<T>{});
}

int main()
{
	process(123);
	process(2.2);
	process("Test"s);
}
