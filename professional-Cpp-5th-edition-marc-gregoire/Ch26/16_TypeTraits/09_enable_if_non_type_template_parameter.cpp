/*
 * Chapter 26 - enable_if on a Non-type Template Parameter
 *
 * The same SFINAE selection between checkType() overloads, but here enable_if_t
 * is placed on an extra defaulted non-type template parameter rather than on
 * the return type. This placement is the technique to use when a function (for
 * example a constructor) has no return type to attach enable_if to.
 */

#include <print>
#include <type_traits>
#include <string>

using namespace std;

template <typename T1, typename T2, enable_if_t<is_same_v<T1, T2>>* = nullptr>
bool checkType(const T1& t1, const T2& t2)
{
	println("'{}' and '{}' are the same types.", t1, t2);
	return true;
}

template <typename T1, typename T2, enable_if_t<!is_same_v<T1, T2>>* = nullptr>
bool checkType(const T1& t1, const T2& t2)
{
	println("'{}' and '{}' are different types.", t1, t2);
	return false;
}

int main()
{
	checkType(1, 32);
	checkType(1, 3.01);
	checkType(3.01, "Test"s);
}
