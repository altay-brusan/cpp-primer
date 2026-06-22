/*
 * Chapter 27 - Data Race Demonstration (Non-Atomic Counter)
 *
 * Ten threads each increment a shared plain int 100 times, so the expected result is
 * 1000. Because ++counter on a non-atomic int is a load-modify-store that can interleave
 * between threads, this program contains a data race and usually prints a value below
 * 1000 that varies from run to run. It exists to motivate the atomic versions that
 * follow.
 *
 * Key notes:
 *   - Intentionally buggy: the unsynchronized shared write is undefined behavior.
 */

#include <print>
#include <chrono> // newest MSVC no longer pulls <chrono> in transitively via <thread>
#include <vector>
#include <thread>

using namespace std;

void increment(int& counter)
{
	for (int i{ 0 }; i < 100; ++i) {
		++counter;
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
