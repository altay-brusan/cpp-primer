/*
 * Chapter 19 - Returning a Lambda from a Function
 *
 * Shows how to return a lambda expression from a function by wrapping it in an
 * std::function. multiplyBy2Lambda(int x) captures x by value and returns a lambda of
 * type function<int(void)> that yields 2 * x. Because x is captured by value, the returned
 * closure stays valid after the function exits - capturing by reference here would be a
 * dangling-reference bug. The commented alternative shows the same with function return
 * type deduction (auto).
 */
#include <print>
#include <functional>

using namespace std;

function<int(void)> multiplyBy2Lambda(int x)
{
	return [x]{ return 2 * x; };
}

// Using function return type deduction
//auto multiplyBy2Lambda(int x)
//{
//	return [x]{ return 2 * x; };
//}

int main()
{
	//function<int(void)> fn{ multiplyBy2Lambda(5) };
	//println("{}", fn());

	auto fn{ multiplyBy2Lambda(5) };
	println("{}", fn());
}