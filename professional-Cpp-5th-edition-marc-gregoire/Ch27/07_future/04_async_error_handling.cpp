/*
 * Chapter 27 - Error Handling with Futures
 *
 * Futures make cross-thread error handling easy: an exception thrown inside an async task
 * is captured and re-thrown when the result is retrieved. Here calculate() throws a
 * runtime_error while running under launch::async; the exception is stored in the future
 * and surfaces from future.get() in the main thread, where a try/catch handles it.
 */

#include <print>
#include <future>
#include <stdexcept>

using namespace std;

int calculate()
{
	throw runtime_error{ "Exception thrown from calculate()." };
}

int main()
{
	// Use the launch::async policy to force asynchronous execution.
	auto myFuture{ async(launch::async, calculate) };

	// Do some more work...

	// Get the result.
	try {
		int result{ myFuture.get() };
		println("Result: {}", result);
	} catch (const exception& ex) {
		println("Caught exception: {}", ex.what());
	}
}
