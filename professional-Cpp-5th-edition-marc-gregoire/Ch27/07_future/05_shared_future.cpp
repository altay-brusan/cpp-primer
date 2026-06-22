/*
 * Chapter 27 - std::shared_future: Broadcasting a Value to Many Threads
 *
 * A regular future can be consumed by only one get(); a std::shared_future can be copied
 * and waited on by many threads. Here two async tasks each hold a copy of the same
 * shared_future and block on get(), acting as a one-to-many signal. The main thread waits
 * (via void promises) until both have started, then sets a single promise's value to wake
 * both tasks at once.
 */

#include <thread>
#include <future>

using namespace std;

int main()
{
	promise<void> thread1Started, thread2Started;

	promise<int> signalPromise;
	auto signalFuture{ signalPromise.get_future().share() };
	//shared_future<int> signalFuture{ signalPromise.get_future() };

	auto function1{ [&thread1Started, signalFuture] {
		thread1Started.set_value();
		// Wait until parameter is set.
		int parameter{ signalFuture.get() };
		// ...
	} };

	auto function2{ [&thread2Started, signalFuture] {
		thread2Started.set_value();
		// Wait until parameter is set.
		int parameter{ signalFuture.get() };
		// ...
	} };

	// Run both lambda expressions asynchronously.
	// Remember to capture the future returned by async()!
	auto result1{ async(launch::async, function1) };
	auto result2{ async(launch::async, function2) };

	// Wait until both threads have started.
	thread1Started.get_future().wait();
	thread2Started.get_future().wait();

	// Both threads are now waiting for the parameter.
	// Set the parameter to wake up both of them.
	signalPromise.set_value(42);
}