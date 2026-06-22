/*
 * Chapter 7 - Multidimensional Free Store Arrays
 *
 * A free-store multidimensional array is NOT a single contiguous block like its stack
 * cousin. `new char[xDim][yDim]` will not even compile. Instead you build a "jagged" two
 * level structure: first allocate an array of `xDim` row pointers, then allocate each row
 * with its own `new char[yDim]`. Deallocation must mirror this exactly in reverse - free
 * each row, then free the array of row pointers. Forgetting any row leaks `yDim` chars.
 *
 * Key notes:
 *   - `char**` here is the outer pointer; `myArray[i]` is itself a heap-allocated `char*`.
 *   - Each `new[]` requires a paired `delete[]`; mixing forms is undefined behavior.
 *   - Memory is fragmented - rows can be scattered, hurting cache performance. A flat
 *     `new char[xDim * yDim]` indexed as `x * yDim + y` is faster.
 *   - `char**&` (reference-to-pointer) lets the cleanup function null out the caller's
 *     variable so a stale pointer cannot be dereferenced later.
 *   - This raw-pointer pattern is brittle on exceptions; in modern code prefer
 *     `std::vector<std::vector<char>>` or a custom `Matrix<T>` class template.
 */

#include <cstddef>

using namespace std;

char** allocateCharacterBoard(size_t xDimension, size_t yDimension)
{
	char** myArray{ new char* [xDimension] }; // Allocate first dimension (array of row pointers)

	for (size_t i{ 0 }; i < xDimension; ++i) {
		myArray[i] = new char[yDimension];    // Allocate ith subarray - rows live independently
	}

	return myArray;
}

void releaseCharacterBoard(char**& myArray, size_t xDimension)
{
	for (size_t i{ 0 }; i < xDimension; ++i) {
		delete [] myArray[i];    //  Delete ith subarray - must match `new char[yDimension]`
		myArray[i] = nullptr;
	}

	delete [] myArray;           //  Delete first dimension - matches `new char*[xDimension]`
	myArray = nullptr;           //  Caller's pointer is now safely nulled (reference parameter)
}

int main()
{
	const size_t xDimension{ 7 };
	const size_t yDimension{ 13 };
	char** board{ allocateCharacterBoard(xDimension, yDimension) };
	releaseCharacterBoard(board, xDimension);
}

