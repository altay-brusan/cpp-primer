/*
 * Chapter 19 - Recursive Lambda with an Explicit Object Parameter
 *
 * Demonstrates a self-recursive lambda using the C++23 deduced "this" / explicit object
 * parameter. The first parameter, this auto& self, names the lambda's own closure, letting
 * the body call self(...) to recurse - here computing Fibonacci numbers - without needing
 * an std::function or a separate named function.
 */
#include <print>

using namespace std;

int main()
{
	auto fibonacci = [](this auto& self, int n) {
		if (n < 2) {
			return n;
		}
		return self(n - 1) + self(n - 2);
	};

	println("First 20 Fibonacci numbers:");
	for (int i{ 0 }; i < 20; ++i) {
		print("{} ", fibonacci(i));
	}
}