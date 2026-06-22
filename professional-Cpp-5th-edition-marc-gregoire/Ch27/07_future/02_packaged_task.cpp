/*
 * Chapter 27 - std::packaged_task
 *
 * A std::packaged_task wraps a callable so that its return value (or exception) is
 * automatically delivered through an associated std::future. main() wraps calculateSum
 * in a packaged_task, retrieves its future, then moves the task into a thread and runs it
 * with arguments. future.get() retrieves the computed sum once the task completes.
 */

#include <print>
#include <thread>
#include <future>
#include <utility>

using namespace std;

int calculateSum(int a, int b)
{
	return a + b;
}

int main()
{
	// Create a packaged task to run calculateSum.
	packaged_task task{ calculateSum };
	// Get the future for the result of the packaged task.
	auto theFuture{ task.get_future() };
	// Create a thread, move the packaged task into, and
	// execute the packaged task with the given arguments.
	jthread theThread{ move(task), 39, 3 };
	
	// Do some more work...

	// Get the result.
	int result{ theFuture.get() };
	println("Result: {}", result);

	// No need to manually call join(), as we are using jthread.
}
