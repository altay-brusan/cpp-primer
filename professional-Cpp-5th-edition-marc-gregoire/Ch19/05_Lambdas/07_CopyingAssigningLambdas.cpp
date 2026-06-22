/*
 * Chapter 19 - Default-Constructing, Copying, and Assigning Lambdas
 *
 * Demonstrates two C++20 features for stateless lambdas. First, a lambda in an unevaluated
 * context: decltype([](int a, int b) { return a + b; }) names a lambda's closure type
 * without evaluating it, here aliased to LambdaType and default-constructed inside
 * getLambda(). Second, stateless lambdas are now default-constructible, copy-constructible,
 * and copy-assignable, as shown with lambda2, copy, and the copy = lambda2 assignment.
 */
#include <print>

using namespace std;

using LambdaType = decltype([](int a, int b) { return a + b; }); // Unevaluated.

LambdaType getLambda()
{
	return LambdaType{}; // Default construction.
}

int main()
{
	auto lambda{ [](int a, int b) { return a + b; } }; // A stateless lambda.
	decltype(lambda) lambda2;	// Default construction.
	auto copy{ lambda };		// Copy construction.
	copy = lambda2;				// Copy assignment.

	println("{}", lambda(1, 2));
	println("{}", lambda2(1, 2));
	println("{}", copy(1, 2));
	println("{}", getLambda()(1, 2));
}
