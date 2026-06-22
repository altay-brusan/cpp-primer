/*
 * Chapter 14 - Capturing a Stack Trace
 *
 * Uses the C++23 std::stacktrace (from <stacktrace>) to capture the call stack
 * at a point in execution. A->B->C call chain calls stacktrace::current() in C()
 * and passes it to handleStackTrace(), which reports size() and formats the whole
 * trace directly with std::format/println. Stack traces are valuable for
 * diagnosing where errors originate.
 *
 * Key notes:
 *   - If formatting a stacktrace directly isn't supported yet, to_string(trace)
 *     is shown as a fallback (commented out).
 */

#include <print>
#include <stacktrace>

using namespace std;

void handleStackTrace(const stacktrace& trace)
{
	println("  Stack trace information:");
	println("    There are {} frames in the stack trace.", trace.size());
	println("    Here are all the frames:");
	println("---------------------------------------------------------");
	println("{}", trace);
	// If the above statement doesn't work yet, you can use the following:
	//println("{}", to_string(trace));
	println("---------------------------------------------------------");
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
