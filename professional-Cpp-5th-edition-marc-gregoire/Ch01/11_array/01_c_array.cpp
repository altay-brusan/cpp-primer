/*
 * Chapter 1 - C-Style Arrays
 *
 * A C-style array holds a fixed number of same-typed elements indexed from 0. The size must
 * be a constant expression known at compile time and cannot change at run time. Prefer
 * std::array (fixed size) or std::vector (dynamic size) in new code - they keep their size,
 * do not decay to pointers, and play with the rest of the Standard Library.
 *
 * Key notes:
 *   - Indexing starts at 0. The last valid index is size - 1.
 *   - Zero-fill the whole array with "int arr[3] {};" - an empty brace-initializer.
 *     Partial init ("int arr[3] { 2 };") sets the first element and zeros the rest.
 *   - Omit the size when an initializer list is present and the compiler counts:
 *     "int arr[] { 1, 2, 3, 4 };" creates an array of 4.
 *   - Get the element count with std::size(arr) (in <array>/<iterator>) - returns size_t.
 *     The older trick "sizeof(arr) / sizeof(arr[0])" still works but only on real arrays,
 *     not on pointers (it silently gives the wrong answer for a pointer parameter).
 *   - Passing an array to a function decays it to a pointer; the size information is lost.
 *   - Multidimensional arrays: "char board[3][3];" - row-major in memory.
 */

#include <cstddef>
#include <array>

int main()
{
	{
		int myArray[3];
		myArray[0] = 0;
		myArray[1] = 0;
		myArray[2] = 0;
	}

	{
		int myArray[3] = { 0 };
	}

	{
		int myArray[3] = {};
	}

	{
		int myArray[3]{};
	}

	{
		int myArray[]{ 1, 2, 3, 4 }; // The compiler creates an array of 4 elements.
	}

	{
		int myArray[3]{ 2 };
		std::size_t arraySize1{ std::size(myArray) };
		std::size_t arraySize2{ sizeof(myArray) / sizeof(myArray[0]) };
	}

	{
		char ticTacToeBoard[3][3];
		ticTacToeBoard[1][1] = 'o';
	}
}
