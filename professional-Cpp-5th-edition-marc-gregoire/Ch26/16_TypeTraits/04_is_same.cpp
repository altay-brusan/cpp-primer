/*
 * Chapter 26 - Type Relationships: is_same
 *
 * same() uses the is_same_v type relationship trait to report at compile time
 * whether its two arguments have the same type, then prints an appropriate
 * message. Other relationship traits such as is_base_of and is_convertible work
 * the same way.
 */

#include <print>
#include <type_traits>
#include <string>

using namespace std;

template<typename T1, typename T2>
void same(const T1& t1, const T2& t2)
{
	bool areTypesTheSame{ is_same_v<T1, T2> };
	// Or:
	//bool areTypesTheSame{ is_same<T1, T2>::value };

	println("'{}' and '{}' are {} types.", t1, t2,
		(areTypesTheSame ? "the same" : "different"));
}

int main()
{
	same(1, 32);
	same(1, 3.01);
	same(3.01, "Test"s);
}
