/*
 * Chapter 27 - The Double-Checked Locking Pattern
 *
 * Double-checked locking initializes a shared resource once while avoiding the cost of
 * locking on every call. A thread first checks an atomic<bool> flag without locking; only
 * if it is still false does it take the mutex and check again before initializing and
 * setting the flag. The atomic flag is essential here to avoid a data race on the check.
 * (std::call_once, shown earlier, is the simpler and usually preferred alternative.)
 *
 * Key notes:
 *   - The guard flag must be atomic; a plain bool would reintroduce a data race.
 */

#include <print>
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>

using namespace std;

void initializeSharedResources()
{
	// ... Initialize shared resources to be used by multiple threads.

	println("Shared resources initialized.");
}

atomic<bool> g_initialized{ false };
mutex g_mutex;

void processingFunction()
{
	if (!g_initialized) {
		unique_lock lock{ g_mutex };
		if (!g_initialized) {
			initializeSharedResources();
			g_initialized = true;
		}
	}
	print("1");
}

int main()
{
	vector<jthread> threads;

	for (int i{ 0 }; i < 5; ++i) {
		threads.emplace_back(processingFunction);
	}

	// No need to manually call join(), as we are using jthread.
}
