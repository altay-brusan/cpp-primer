/*
 * Chapter 27 - std::latch: Waiting for Workers to Finish
 *
 * A std::latch is a single-use counter that lets one thread block until a number of
 * events have happened. It is initialized with the worker count; each worker calls
 * count_down() when its work is done, and the main thread calls wait() to block until
 * the counter reaches zero. Here ten worker jthreads run, and main() waits on the latch
 * before reporting that all are finished.
 */

#include <print>
#include <chrono> // newest MSVC no longer pulls <chrono> in transitively via <thread>
#include <thread>
#include <vector>
#include <latch>

using namespace std;

int main()
{
	// Launch a number of threads to do some work.
	constexpr unsigned numberOfWorkerThreads{ 10 };
	latch latch{ numberOfWorkerThreads };
	vector<jthread> threads;
	for (unsigned i{ 0 }; i < numberOfWorkerThreads; ++i) {
		threads.emplace_back([&latch, i] {
			// Do some work...
			print("{} ", i);
			this_thread::sleep_for(1s);
			print("{} ", i);

			// When work is done, decrease the latch counter.
			latch.count_down();
		});
	}
	// Wait for all worker threads to finish.
	latch.wait();
	println("\nAll worker threads are finished.");
}
