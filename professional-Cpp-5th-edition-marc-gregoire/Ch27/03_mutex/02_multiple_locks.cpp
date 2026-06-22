/*
 * Chapter 27 - Acquiring Multiple Locks with std::lock()
 *
 * To lock two mutexes at once without risking a deadlock, the code constructs two
 * unique_locks with std::defer_lock (so they do not lock during construction) and then
 * calls std::lock() to acquire both in a deadlock-free order. The unique_locks release
 * the mutexes automatically at scope exit. This is a structural example: there is no
 * console output and the threads are not actually launched.
 */

#include <mutex>

using namespace std;

mutex mut1;
mutex mut2;

void process()
{
	unique_lock lock1{ mut1, defer_lock };
	unique_lock lock2{ mut2, defer_lock };
	lock(lock1, lock2);

	// Locks acquired.

} // Locks automatically released.

int main()
{
	process();
}
