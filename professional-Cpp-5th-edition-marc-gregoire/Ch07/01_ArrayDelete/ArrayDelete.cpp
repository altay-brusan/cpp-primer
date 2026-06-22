/*
 * Chapter 7 - Deleting Arrays
 *
 * Every allocation made with `new[]` must be released with `delete[]`, and every allocation
 * made with `new` must be released with plain `delete`. Mismatching the two forms is
 * undefined behavior: some compilers will only run the destructor of the first element,
 * others will corrupt the free store because `new` and `new[]` can use different allocators.
 * When you have an array of raw pointers, each pointed-to object must be deleted on its
 * own before the top-level array is freed - the array deleter does not chase pointers for
 * you.
 *
 * Key notes:
 *   - `new T[n]` value-initializes objects (default constructor runs n times); `delete[]`
 *     destroys them in reverse order.
 *   - `delete[] mySimplePtrArray` on a `Simple**` only frees the pointer array itself, NOT
 *     the `Simple` instances each slot points to.
 *   - Setting a pointer to `nullptr` after `delete[]` prevents accidental reuse of a
 *     dangling pointer; `delete` on `nullptr` is a no-op.
 *   - In modern C++ prefer `std::vector<Simple>` or `std::vector<std::unique_ptr<Simple>>`
 *     over either pattern shown here.
 */

#include <print>
#include <cstddef>

using namespace std;

class Simple
{
public:
	Simple() { println("Simple constructor called!"); }
	~Simple() { println("Simple destructor called!"); }
};

int main()
{
	Simple* mySimpleArray{ new Simple[4] };           // new[] runs the default ctor 4 times
	// Use mySimpleArray...
	delete[] mySimpleArray;                           // delete[] runs the dtor 4 times
	mySimpleArray = nullptr;


	const size_t size{ 4 };
	Simple** mySimplePtrArray{ new Simple*[size] };   // Array of raw pointers - slots uninitialized

	// Allocate an object for each pointer.
	for (size_t i{ 0 }; i < size; ++i) { mySimplePtrArray[i] = new Simple{}; }  // one new per slot

	// Use mySimplePtrArray ...

	// Delete each allocated object.
	for (size_t i{ 0 }; i < size; ++i) {
		delete mySimplePtrArray[i];                   // single-object delete - matches `new Simple{}`
		mySimplePtrArray[i] = nullptr;
	}

	// Delete the array itself.
	delete[] mySimplePtrArray;                        // array delete - matches `new Simple*[size]`
	mySimplePtrArray = nullptr;
}
