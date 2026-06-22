/*
 * Chapter 14 - Iterating Over Stack Trace Frames
 *
 * Like 01_stacktrace, but instead of formatting the whole trace at once, it
 * iterates the std::stacktrace and prints each std::stacktrace_entry frame
 * individually via frame.description(). A std::stacktrace is a range of frames,
 * each exposing details about one level of the call stack.
 */

#include <print>
#include <stacktrace>

using namespace std;

void handleStackTrace(const stacktrace& trace)
{
	println("  Stack trace information:");
	println("    There are {} frames in the stack trace.", trace.size());
	println("    Here are the descriptions of all the frames:");
	for (unsigned index{ 0 }; auto&& frame : trace) {
		println("      {} -> {}", index++, frame.description());
	}
}

void C()
{
	println("Entered C().");
	handleStackTrace(stacktrace::current());
}

void B()
{
	println("Entered B().");
	C();
}

void A()
{
	println("Entered A().");
	B();
}

int main()
{
	A();
}
