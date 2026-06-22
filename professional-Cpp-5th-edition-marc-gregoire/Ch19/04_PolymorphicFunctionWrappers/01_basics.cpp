/*
 * Chapter 19 - std::function Basics
 *
 * Introduces std::function, the polymorphic function wrapper from <functional>, which can
 * hold anything callable matching a given signature. An std::function<void(int,
 * string_view)> is created to point at func(), called, then reassigned to func2() and
 * called again - the same wrapper variable storing different callables over time. The
 * second block shows the same thing relying on class template argument deduction
 * (function f1 { func }).
 *
 * Key notes:
 *   - Using auto instead would deduce a plain function pointer, not an std::function.
 */
#include <print>
#include <functional>
#include <string_view>

using namespace std;

void func(int num, string_view str)
{
	println("func({}, {})", num, str);
}

void func2(const int& num, string_view str)
{
	println("func2({}, {})", num, str);
}

int main()
{
	{
		function<void(int, string_view)> f1{ func };
		f1(1, "test");
		
		f1 = func2;
		f1(1, "test");
	}

	{
		// With class template argument deduction
		function f1{ func };
		f1(1, "test");

		f1 = func2;
		f1(1, "test");
	}
}
