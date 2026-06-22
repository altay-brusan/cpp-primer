/*
 * Chapter 27 - Thread Local Storage with thread_local
 *
 * A variable marked thread_local gets one unique copy per thread, initialized once per
 * thread and living for the thread's whole duration. Here global k is ordinary (shared
 * across all threads) while n is thread_local. Running the function on two sequential
 * threads shows k keeps incrementing across threads, while each thread sees its own
 * fresh n starting at 0.
 */

#include <print>
#include <thread>

using namespace std;

int k;
thread_local int n;

void threadFunction(int id)
{
	println("Thread {}: k={}, n={}", id, k, n);
	++n;
	++k;
}

int main()
{
	thread t1{ threadFunction, 1 };
	t1.join();

	thread t2{ threadFunction, 2 };
	t2.join();
}