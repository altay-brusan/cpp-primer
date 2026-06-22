/*
 * Chapter 26 - Replacing enable_if with a requires Clause
 *
 * The clearest version of the checkType() overloads: a requires clause using
 * is_same_v constrains one overload to identical types and the other to
 * differing types. C++20 concepts and requires clauses express the same intent
 * as the earlier enable_if/SFINAE versions far more readably.
 */

#include <print>
#include <type_traits>
#include <string>

using namespace std;

template <typename T1, typename T2> requires is_same_v<T1, T2>
bool checkType(const T1& t1, const T2& t2)
{
	println("'{}' and '{}' are the same types.", t1, t2);
	return true;
}

template <typename T1, typename T2> requires !is_same_v<T1, T2>
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
