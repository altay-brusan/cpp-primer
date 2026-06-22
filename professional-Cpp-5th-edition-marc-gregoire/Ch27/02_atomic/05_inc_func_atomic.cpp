/*
 * Chapter 27 - Fixing the Data Race with std::atomic
 *
 * Same ten-threads-incrementing scenario as the non-atomic sample, but the shared
 * counter is now an std::atomic<int>. The ++ operator on an atomic loads, increments,
 * and stores in a single uninterruptible transaction, so no explicit synchronization is
 * needed and the result is reliably 1000 every run.
 */

#include <print>
#include <chrono> // newest MSVC no longer pulls <chrono> in transitively via <thread>
#include <atomic>
#include <vector>
#include <thread>

using namespace std;

void increment(atomic<int>& counter)
{
	for (int i{ 0 }; i < 100; ++i) {
		++counter;
		this_thread::sleep_for(1ms);
	}
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
