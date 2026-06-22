/*
 * Chapter 27 - std::async
 *
 * std::async runs a function and hands back a std::future for its result, choosing
 * whether to run it on a new thread or lazily (commented alternatives show the explicit
 * launch::async and launch::deferred policies). main() launches calculateSum
 * asynchronously and later calls get() on the future to obtain the result, blocking if
 * the work has not yet finished.
 */

#include <print>
#include <future>

using namespace std;

int calculateSum(int a, int b)
{
	return a + b;
}

int main()
{
	auto myFuture{ async(calculateSum, 39, 3) };
	//auto myFuture{ async(launch::async, calculateSum, 39, 3) };
	//auto myFuture{ async(launch::deferred, calculateSum, 39, 3) };

	// Do some more work...

	// Get the result.
	int result{ myFuture.get() };
	println("Result: {}", result);
}
