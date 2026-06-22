/*
 * Chapter 27 - Launching a Thread with a Function Pointer
 *
 * The simplest way to start a thread: hand std::thread a free function plus its
 * arguments. The thread constructor is a variadic template, so counter() can take as
 * many parameters as needed (here an id and an iteration count); the arguments are
 * copied into internal storage for the new thread. Two threads run counter() in
 * parallel, and main() calls join() on each so it blocks until they finish.
 *
 * Key notes:
 *   - A joinable thread must be join()'d or detach()'d before it is destroyed,
 *     otherwise its destructor calls std::terminate().
 *   - Output from the two threads may interleave; cout access itself is thread-safe.
 */

#include <print>
#include <thread>

using namespace std;

void counter(int id, int numIterations)
{
	for (int i{ 0 }; i < numIterations; ++i) {
		println("Counter {} has value {}", id, i);
		//cout << format("Counter {} has value {}", id, i) << endl;
	}
}

int main()
{
	thread t1{ counter, 1, 6 };
	thread t2{ counter, 2, 4 };
	t1.join();
	t2.join();
}
