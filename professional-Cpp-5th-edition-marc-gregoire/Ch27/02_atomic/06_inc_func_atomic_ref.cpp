/*
 * Chapter 27 - Fixing the Data Race with std::atomic_ref
 *
 * C++20's std::atomic_ref applies atomic operations to an existing non-atomic object
 * through a reference, instead of storing its own copy as std::atomic does. Here the
 * shared counter stays a plain int; each thread wraps it in a local atomic_ref and
 * increments through that, making the updates race-free and yielding 1000.
 *
 * Key notes:
 *   - An atomic_ref must live no longer than the object it refers to, and while any
 *     atomic_ref refers to an object you must access that object only through it.
 */

#include <print>
#include <chrono> // newest MSVC no longer pulls <chrono> in transitively via <thread>
#include <atomic>
#include <vector>
#include <thread>
#include <functional>

using namespace std;

void increment(int& counter)
{
	atomic_ref<int> atomicCounter{ counter };
	for (int i{ 0 }; i < 100; ++i) {
		++atomicCounter;
		this_thread::sleep_for(1ms);
	}
}

int main()
{
	int counter{ 0 };
	vector<jthread> threads;

	for (int i{ 0 }; i < 10; ++i) {
		threads.emplace_back(increment, ref(counter));
	}

	for (auto& t : threads) {
		t.join();
	}

	println("Result = {}", counter);
}
