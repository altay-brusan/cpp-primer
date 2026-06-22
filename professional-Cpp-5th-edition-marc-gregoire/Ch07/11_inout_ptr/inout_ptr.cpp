/*
 * Chapter 7 - std::inout_ptr / std::out_ptr (C++23)
 *
 * Many C-style libraries allocate through a `T**` out-parameter: you pass the address of
 * your pointer, the function fills it in, and you are expected to free it later with the
 * matching deallocator. Mixing that pattern with smart pointers used to be ugly - you
 * had to receive into a raw pointer first, then `.reset()` the smart pointer. C++23
 * introduces `std::inout_ptr` and `std::out_ptr` adapters (in `<memory>`) that hand the
 * legacy API a temporary `T**`, then on destruction copy the result back into the smart
 * pointer's ownership.
 *
 * Key notes:
 *   - `out_ptr(sp)`  - use when the C API ONLY writes the pointer (does not read it
 *     first). On destruction of the adapter, the previous resource in `sp` is freed
 *     and the new one is adopted.
 *   - `inout_ptr(sp)` - use when the C API may read the existing pointer (e.g. realloc-
 *     style). It also releases ownership from `sp` before handing it over.
 *   - Works with `unique_ptr` (including those carrying custom deleters) and with raw
 *     pointers; behavior for `shared_ptr` is more constrained.
 *   - The adapter object must be a temporary or a short-lived local - it commits the
 *     write only when it is destroyed.
 *
 * Example:
 *     unique_ptr<int, decltype(&my_free)> p(nullptr, my_free);
 *     my_alloc(42, std::out_ptr(p));   // C API writes through, p now owns the result.
 */

#include <print>
#include <memory>

using namespace std;

using errorcode = int;

// A typical C-style API: returns an error code, allocates through a T** out parameter.
errorcode my_alloc(int value, int** data)
{
	*data = new int{ value };
	println("Allocated");
	return 0;
}

// Matching C-style deallocator.
errorcode my_free(int* data)
{
	delete data;
	println("Freed");
	return 0;
}

int main()
{
	{
		// Manual style (pre-C++23): allocate into a raw temporary, then reset() the smart pointer.
		unique_ptr<int, decltype(&my_free)> myIntSmartPtr(nullptr, my_free);
		int* data{ nullptr };
		my_alloc(42, &data);          // C API writes the raw pointer.
		myIntSmartPtr.reset(data);    // Manually hand ownership over.
	}

	{
		// C++23 style: inout_ptr does the dance for us.
		unique_ptr<int, decltype(&my_free)> myIntSmartPtr(nullptr, my_free);
		my_alloc(42, inout_ptr(myIntSmartPtr));   // Adapter transfers ownership on destruction.
	}
}
