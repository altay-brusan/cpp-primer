/*
 * Chapter 27 - std::jthread and Cooperative Cancellation
 *
 * C++20's std::jthread is like std::thread but it automatically join()s in its
 * destructor and supports cooperative cancellation. A callable can take a std::stop_token
 * as its first parameter and poll token.stop_requested() to decide when to stop. main()
 * runs two worker jthreads, sleeps, then calls request_stop() on each to ask them to
 * wind down cleanly.
 *
 * Key notes:
 *   - Cancellation is cooperative: the thread itself must periodically check the token.
 *   - The stop_token is supplied automatically by jthread; you do not pass it yourself.
 */

#include <print>
#include <chrono> // newest MSVC no longer pulls <chrono> in transitively via <thread>
#include <thread>
#include <stop_token>

using namespace std;

void threadFunction(stop_token token, int id)
{
	while (!token.stop_requested()) {
		println("Thread {} doing some work.", id);
		this_thread::sleep_for(500ms);
	}
	println("Stop requested for thread {}.", id);
}

int main()
{
	jthread job1{ threadFunction, 1 };
	jthread job2{ threadFunction, 2 };

	this_thread::sleep_for(2s);
	println("main() is ending.");
	
	job1.request_stop();
	job2.request_stop();
}
