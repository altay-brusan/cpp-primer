/*
 * Chapter 27 - Copying and Rethrowing Exceptions Across Threads
 *
 * An exception thrown in one thread cannot be caught in another, and an uncaught one
 * calls std::terminate(). To transfer an exception across threads, the worker catches
 * it and captures it with std::current_exception() into an std::exception_ptr passed by
 * reference. After join(), the main thread checks the exception_ptr (a NullablePointer)
 * and, if non-null, re-raises it with std::rethrow_exception(), effectively moving the
 * exception from the worker thread into the main thread.
 */

#include <print>
#include <thread>
#include <stdexcept>

using namespace std;

void doSomeWork()
{
	for (int i{ 0 }; i < 5; ++i) {
		println("{}", i);
	}
	println("Thread throwing a runtime_error exception...");
	throw runtime_error{ "Exception from thread" };
}

void threadFunc(exception_ptr& err)
{
	try {
		doSomeWork();
	} catch (...) {
		println("Thread caught exception, returning exception...");
		err = current_exception();
	}
}

void doWorkInThread()
{
	exception_ptr error;
	// Launch thread.
	jthread t{ threadFunc, ref(error) };
	// Wait for thread to finish.
	t.join();
	// See if thread has thrown any exception.
	if (error) {
		println("Main thread received exception, rethrowing it...");
		rethrow_exception(error);
	} else {
		println("Main thread did not receive any exception.");
	}
}

int main()
{
	try {
		doWorkInThread();
	} catch (const exception& e) {
		println("Main function caught: '{}'", e.what());
	}
}
