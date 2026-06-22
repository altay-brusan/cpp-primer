/*
 * Chapter 7 - shared_ptr Managing a Non-Memory Resource
 *
 * Smart pointers are not limited to managing heap memory. With a custom deleter a
 * `shared_ptr` can wrap any resource that has an "open" and a "close" step: file
 * handles, network sockets, database connections, OS handles, and so on. When the last
 * `shared_ptr` to the handle is destroyed, the deleter runs and the resource is
 * released - giving you RAII semantics for legacy C-style APIs.
 *
 * Key notes:
 *   - `fopen` returns a `FILE*`; the deleter calls `fclose` on it (with a `nullptr`
 *     guard, since `fclose(nullptr)` is undefined).
 *   - C++ has proper RAII file streams in `<fstream>` already - this example is about
 *     the technique, not because `FILE*` is the recommended way to do I/O.
 *   - The same pattern fits any C library: `SDL_CreateWindow`/`SDL_DestroyWindow`,
 *     `sqlite3_open`/`sqlite3_close`, `OpenHandle`/`CloseHandle`, etc.
 *   - The `#pragma warning( disable : 4996)` block silences MSVC's `fopen_s` nag for
 *     this teaching example only.
 */

#include <print>
#include <memory>
#include <iostream>
#include <cstdio>

using namespace std;

void close(FILE* filePtr)
{
	if (filePtr == nullptr) { return; }
	fclose(filePtr);
	println("File closed.");
}

int main()
{
#if defined(_MSC_VER)
	// Disable the following Microsoft Visual C++ warning for this example:
	// C4996: 'fopen': This function or variable may be unsafe. Consider using fopen_s instead.
	#pragma warning( disable : 4996)
#endif

	FILE* f{ fopen("data.txt", "w") };
	shared_ptr<FILE> filePtr{ f, close };   // deleter `close` runs when filePtr's count hits 0
	if (filePtr == nullptr) {
		println(cerr, "Error opening file.");
	} else {
		println("File opened.");
		// Use filePtr
	}
}
