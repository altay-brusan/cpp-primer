/*
 * Chapter 27 - Inter-Thread Communication with std::promise and std::future
 *
 * A std::promise is the producing end and its std::future the consuming end of a
 * one-shot result channel. main() creates a promise, grabs its future, then moves the
 * promise into a worker thread. The worker stores a result with set_value(); main() calls
 * future.get(), which blocks until the value is available and then returns it.
 */

#include <print>
#include <thread>
#include <future>
#include <utility>

using namespace std;

void doWork(promise<int> thePromise)
{
	// ... Do some work ...
	// And ultimately store the result in the promise.
	thePromise.set_value(42);
}

int main()
{
	// Create a promise to pass to the thread.
	promise<int> myPromise;
	// Get the future of the promise.
	auto theFuture{ myPromise.get_future() };
	// Create a thread and move the promise into it.
	jthread theThread{ doWork, move(myPromise) };

	// Do some more work...

	// Get the result.
	int result{ theFuture.get() };
	println("Result: {}", result);

	// No need to manually call join(), as we are using jthread.
}
