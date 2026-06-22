/*
 * Chapter 27 - Waiting on Atomic Variables (wait / notify)
 *
 * C++20 adds wait(), notify_one(), and notify_all() to std::atomic for efficiently
 * blocking until a value changes. The worker thread calls value.wait(0), which blocks
 * while the atomic still equals 0. The main thread sleeps, sets value to 1, and calls
 * notify_all(), waking the worker, which then observes the new value.
 */

#include <print>
#include <chrono> // newest MSVC no longer pulls <chrono> in transitively via <thread>
#include <atomic>
#include <thread>

using namespace std;

int main()
{
	atomic<int> value{ 0 };

	jthread job{ [&value] {
		println("Thread starts waiting.");
		value.wait(0);
		println("Thread wakes up, value = {}", value.load());
	} };

	this_thread::sleep_for(2s);

	println("Main thread is going to change value to 1.");
	value = 1;
	value.notify_all();

	// No need to manually call join(), as we are using jthread.
}
