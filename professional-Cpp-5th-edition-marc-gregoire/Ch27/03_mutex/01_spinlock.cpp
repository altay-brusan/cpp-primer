/*
 * Chapter 27 - Spinlock with std::atomic_flag
 *
 * A spinlock is a mutex implemented with a busy loop: a thread repeatedly calls
 * test_and_set() on an atomic_flag until it succeeds in acquiring the lock, does its
 * work on the shared data, then clear()s the flag to release it. atomic_flag is always
 * lock free. Fifty threads each append to a shared vector under the spinlock; the final
 * element count should equal threads times loops.
 *
 * Key notes:
 *   - Spinlocks waste CPU while spinning, so use them only when locks are held briefly.
 */

#include <print>
#include <atomic>
#include <vector>
#include <thread>
#include <functional>

using namespace std;

static constexpr unsigned NumberOfThreads{ 50 };
static constexpr unsigned LoopsPerThread{ 100 };

void dowork(unsigned threadNumber, vector<unsigned>& data, atomic_flag& spinlock)
{
	for (unsigned i{ 0 }; i < LoopsPerThread; ++i) {
		while (spinlock.test_and_set()) {} // Spins until lock is acquired.
		// Safe to handle shared data...
		data.push_back(threadNumber);
		spinlock.clear();                  // Releases the acquired lock.
	}
}

int main()
{
	vector<unsigned> data;
	atomic_flag dataSpinlock;
	vector<jthread> threads;
	for (unsigned i{ 0 }; i < NumberOfThreads; ++i) {
		threads.emplace_back(dowork, i, ref(data), ref(dataSpinlock));
	}
	for (auto& t : threads) {
		t.join();
	}
	println("data contains {} elements, expected {}.", data.size(),
		NumberOfThreads * LoopsPerThread);
}
