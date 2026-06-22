/*
 * Chapter 27 - std::latch as a Starting Gate
 *
 * This sample uses a latch initialized to 1 the other way around: many worker threads do
 * their CPU-bound setup and then block on startLatch.wait(), while the main thread loads
 * data (I/O bound). Once the data is ready, main() calls count_down() once, driving the
 * counter to zero and releasing all the waiting workers simultaneously. There is no
 * console output in this structural example.
 */

#include <thread>
#include <vector>
#include <latch>

using namespace std;

int main()
{
	latch startLatch{ 1 };
	vector<jthread> threads;

	for (int i{ 0 }; i < 10; ++i) {
		threads.emplace_back([&startLatch] {
			// Do some initialization... (CPU bound)

			// Wait until the latch counter reaches zero.
			startLatch.wait();

			// Process data...
		});
	}

	// Load data... (I/O bound)

	// Once all data has been loaded, decrement the latch counter
	// which then reaches zero and unblocks all waiting threads.
	startLatch.count_down();

	// No need to manually call join(), as we are using jthread.
}
