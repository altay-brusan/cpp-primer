/*
 * Chapter 27 - std::counting_semaphore: Limiting Concurrency
 *
 * A counting semaphore holds a set of slots; acquire() takes one (blocking if none are
 * free) and release() returns one. Here the semaphore is created with 4 slots and ten
 * threads each acquire before doing work and release after, so at most four run their
 * critical section concurrently while the rest wait their turn.
 *
 * Key notes:
 *   - Each worker sleeps several seconds while holding a slot, so this program takes a
 *     while to finish.
 */

#include <print>
#include <chrono> // newest MSVC no longer pulls <chrono> in transitively via <thread>
#include <thread>
#include <vector>
#include <semaphore>

using namespace std;

int main()
{
	counting_semaphore semaphore{ 4 };

	vector<jthread> threads;

	for (int i{ 0 }; i < 10; ++i) {
		threads.emplace_back([&semaphore, i] {
			semaphore.acquire();
			// ... Slot acquired ... (at most 4 threads concurrently)
			print("{}", i);
			this_thread::sleep_for(5s);
			semaphore.release();
		});
	}

	// No need to manually call join(), as we are using jthread.
}
