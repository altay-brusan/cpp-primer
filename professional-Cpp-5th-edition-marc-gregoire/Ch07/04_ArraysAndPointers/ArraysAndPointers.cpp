/*
 * Chapter 7 - Array-Pointer Duality / Arrays Are Pointers!
 *
 * The name of a C-style array decays to a pointer to its first element whenever it is
 * passed to a function. Inside that function there is no way to recover the original
 * length - the array's size is not part of the pointer type. Any number in the brackets
 * of a parameter declaration (`int a[]`, `int a[2]`, `int* a`) is ignored by the compiler;
 * all three are the same function signature. Pass the length explicitly, or pass by
 * reference to a known-sized array, or template over `N`.
 *
 * Key notes:
 *   - Passing an array effectively mimics pass-by-reference: the function mutates the
 *     caller's elements, not a copy.
 *   - `sizeof(theArray)` inside a function with `int* theArray` returns the size of a
 *     pointer, NOT the byte count of the original array.
 *   - `std::size(stackArray)` (since C++17, in `<array>`/`<iterator>`) is the safe way to
 *     ask a stack array for its length; `sizeof(arr) / sizeof(arr[0])` is the legacy idiom.
 *   - `void f(int (&a)[4])` binds only to a stack array of exactly 4 ints; the templated
 *     `f<N>(int (&a)[N])` form lets the compiler deduce `N` for any fixed size.
 *   - Free-store arrays (`new int[n]`) cannot use the `int (&)[N]` reference trick - their
 *     size is not part of the type.
 *   - Since C++20, prefer `std::span<int>` for function parameters - it bundles pointer
 *     and length together.
 */

#include <cstddef>
#include <array>

using namespace std;

void doubleInts(int* theArray, size_t size)  // `size` must come in separately - pointer has no length
{
	for (size_t i{ 0 }; i < size; ++i) {
		theArray[i] *= 2;                    // Mutates the caller's array in place
	}
}

/*
void doubleInts(int theArray[], size_t size)
{
	for (size_t i{ 0 }; i < size; ++i) {
		theArray[i] *= 2;
	}
}
*/

/*
void doubleIntsStack(int (&theArray)[4])
{
	for (size_t i{ 0 }; i < 4; ++i) {
		theArray[i] *= 2;
	}
}
*/

// Function template form - compiler deduces N from the call site, so size is part of the type.
template<size_t N>
void doubleIntsStack(int (&theArray)[N])
{
	for (size_t i{ 0 }; i < N; ++i) {
		theArray[i] *= 2;
	}
}

int main()
{
	int myIntArray[10]{};            // Stack array, zero-initialized
	int* myIntPtr{ myIntArray };     // Array name decays to &myIntArray[0]
	// Access the array through the pointer.
	myIntPtr[4] = 5;                 // ptr[i] is just *(ptr + i) - works on the same memory




	size_t arrSize{ 4 };
	int* freeStoreArray{ new int[arrSize] { 1, 5, 3, 4 } };
	doubleInts(freeStoreArray, arrSize);
	//doubleIntsStack(freeStoreArray);	// Does not work.
	delete[] freeStoreArray;
	freeStoreArray = nullptr;

	int stackArray[] { 5, 7, 9, 11 };
	arrSize = std::size(stackArray);	// Since C++17, requires <array>
	//arrSize = sizeof(stackArray) / sizeof(stackArray[0]); // Pre-C++17, see Ch1
	doubleInts(stackArray, arrSize);          // array name decays to int*
	doubleInts(&stackArray[0], arrSize);      // explicit address-of - identical to above

	doubleIntsStack(stackArray);              // template deduces N = 4 from the type int[4]
}
