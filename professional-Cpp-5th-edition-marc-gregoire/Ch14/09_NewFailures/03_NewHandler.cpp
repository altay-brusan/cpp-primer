/*
 * Chapter 14 - Customizing Allocation Failure with a new_handler
 *
 * Installs a new_handler via set_new_handler(). When new fails, instead of
 * throwing directly it calls the registered handler; here myNewHandler() logs and
 * throws please_terminate_me, a custom exception derived from bad_alloc (the
 * standard requires a new_handler's exception to be bad_alloc or derived). main()
 * catches it and exits cleanly. set_new_handler() returns the previous handler,
 * which is saved and restored.
 *
 * Key notes:
 *   - A new_handler that returns without making memory available, throwing, or
 *     swapping handlers causes an infinite retry loop.
 */

#include <print>
#include <source_location>
#include <limits>
#include <iostream>
#include <cstddef>
#include <new>

using namespace std;

class please_terminate_me : public bad_alloc { };

void myNewHandler()
{
	println(cerr, "Unable to allocate memory.");
	throw please_terminate_me{};
}

int main()
{
	try {
		// Set the new new_handler and save the old one.
		new_handler oldHandler{ set_new_handler(myNewHandler) };

		// Generate allocation error.
		size_t numInts{ numeric_limits<size_t>::max() };
		int* ptr{ new int[numInts] };

		// Reset the old new_handler.
		set_new_handler(oldHandler);
	} catch (const please_terminate_me&) {
		auto location{ source_location::current() };
		println(cerr, "{}({}): Terminating program.",
			location.file_name(), location.line());
		return 1;
	}
}
