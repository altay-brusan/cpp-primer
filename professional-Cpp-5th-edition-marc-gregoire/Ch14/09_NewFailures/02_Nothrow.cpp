/*
 * Chapter 14 - Non-throwing new (nothrow)
 *
 * The C-style alternative to bad_alloc: new(nothrow) returns nullptr on failure
 * instead of throwing. This sample checks the returned pointer against nullptr
 * and reports the failure with source_location. The book does not recommend this
 * form - it is easy to forget the nullptr check, whereas a thrown exception
 * cannot be silently ignored.
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
	size_t integerCount{ numeric_limits<size_t>::max() };
	println("Trying to allocate memory for {} integers.", integerCount);

	int* ptr{ new(nothrow) int[integerCount] };
	if (ptr == nullptr) {
		auto location{ source_location::current() };
		println(cerr, "{}({}): Unable to allocate memory!",
			location.file_name(), location.line());
		// Handle memory allocation failure.
		return 1;
	}
	// Proceed with function that assumes memory has been allocated.
}
