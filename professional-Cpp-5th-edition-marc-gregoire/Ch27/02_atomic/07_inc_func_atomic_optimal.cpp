/*
 * Chapter 27 - Minimizing Synchronization for Performance
 *
 * Atomic operations are correct but not free, so you should minimize them. Each thread
 * accumulates its 100 increments in a plain local int and performs only one atomic
 * operation at the end (counter += result), instead of touching the atomic on every
 * iteration. The result is still reliably 1000 but with far less synchronization
 * overhead; the shared variable must still be atomic since several threads write to it.
 */

#include <print>
#include <chrono> // newest MSVC no longer pulls <chrono> in transitively via <thread>
#include <atomic>
#include <vector>
#include <thread>
#include <functional>

using namespace std;

void increment(atomic<int>& counter)
{
	int result{ 0 };
	for (int i{ 0 }; i < 100; ++i) {
		++result;
		this_thread::sleep_for(1ms);
	}
	counter += result;
}

int main()
{
	atomic<int> counter{ 0 };
	vector<jthread> threads;

	for (int i{ 0 }; i < 10; ++i) {
		threads.emplace_back(increment, ref(counter));
	}

	for (auto& t : threads) {
		t.join();
	}

	println("Result = {}", counter.load());
}
