/*
 * Chapter 14 - Catching Memory Allocation Failures (bad_alloc)
 *
 * By default new and new[] throw std::bad_alloc (from <new>) when they cannot
 * satisfy a request. This sample attempts an absurd allocation (max size_t ints)
 * inside a try block and catches the bad_alloc, using source_location to include
 * the file and line in the message. The book recommends wrapping at least large
 * allocations this way.
 */

#include <print>
#include <source_location>
#include <limits>
#include <iostream>
#include <cstddef>
#include <new>

using namespace std;

int main()
{
	int* ptr{ nullptr };
	size_t integerCount{ numeric_limits<size_t>::max() };
	println("Trying to allocate memory for {} integers.", integerCount);

	try {
		ptr = new int[integerCount];
	} catch (const bad_alloc& e) {
		auto location{ source_location::current() };
		println(cerr, "{}({}): Unable to allocate memory: {}",
			location.file_name(), location.line(), e.what());
		// Handle memory allocation failure.
		return 1;
	}
	// Proceed with function that assumes memory has been allocated.
}
