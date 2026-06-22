/*
 * Chapter 1 - std::array
 *
 * std::array<T, N> (defined in <array>) is a thin wrapper around a fixed-size C array. It
 * knows its own size, does not decay to a pointer when passed around, and exposes begin()/
 * end() so range-based for and the Standard Library algorithms work on it.
 *
 * Key notes:
 *   - Two template parameters: the element type and the element count. Both must be known at
 *     compile time. The size cannot change at run time - use std::vector for that.
 *   - Class template argument deduction (CTAD) lets you skip the angle brackets when there
 *     is an initializer: "std::array arr { 9, 8, 7 };" deduces array<int, 3>.
 *   - .size() returns std::size_t. operator[] is unchecked; .at(i) bounds-checks and throws
 *     std::out_of_range on overflow.
 *   - Useful methods: .front(), .back(), .data() (pointer to first element), .fill(value).
 *   - Pass by reference (or std::span) to avoid copying the whole array.
 */

#include <print>
#include <array>

using namespace std;

int main()
{
	array<int, 3> arr{ 9, 8, 7 };
	// array arr{ 9, 8, 7 };  // Using CTAD
	println("Array size = {}", arr.size());
	println("2nd element = {}", arr[1]);
}
