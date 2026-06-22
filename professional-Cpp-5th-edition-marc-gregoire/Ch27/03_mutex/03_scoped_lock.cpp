/*
 * Chapter 27 - Locking Multiple Mutexes with std::scoped_lock
 *
 * std::scoped_lock is like lock_guard but accepts any number of mutexes, acquiring them
 * all in a deadlock-free order and releasing them when it goes out of scope. Here CTAD
 * deduces the mutex types from the constructor arguments. It is both simpler and more
 * performant than acquiring the locks manually. Structural example with no output.
 */

#include <mutex>

using namespace std;

mutex m1;
mutex m2;

void process()
{
	scoped_lock locks{ m1, m2 }; // Uses class template argument deduction, CTAD.
	//scoped_lock<mutex, mutex> locks{ m1, m2 };

	// Locks acquired.

} // Locks automatically released.

int main()
{
	process();
}
