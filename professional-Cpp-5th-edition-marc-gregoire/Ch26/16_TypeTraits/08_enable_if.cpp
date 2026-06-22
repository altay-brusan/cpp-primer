/*
 * Chapter 26 - SFINAE with enable_if on the Return Type
 *
 * Two checkType() overloads are disabled or enabled by enable_if_t applied to
 * their return type: one is viable only when the types are the same, the other
 * only when they differ. This relies on SFINAE (substitution failure is not an
 * error): when enable_if_t yields no type, that overload is silently removed
 * from the candidate set instead of causing a compile error.
 *
 * Key notes:
 *   - enable_if_t<Condition, Type> is Type when Condition is true and nothing
 *     otherwise; here Type is bool.
 *   - The book recommends concepts or static_assert over SFINAE when possible.
 */

#include <print>
#include <type_traits>
#include <string>

using namespace std;

template <typename T1, typename T2>
enable_if_t<is_same_v<T1, T2>, bool>
checkType(const T1& t1, const T2& t2)
{
	println("'{}' and '{}' are the same types.", t1, t2);
	return true;
}

template <typename T1, typename T2>
enable_if_t<!is_same_v<T1, T2>, bool>
checkType(const T1& t1, const T2& t2)
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
