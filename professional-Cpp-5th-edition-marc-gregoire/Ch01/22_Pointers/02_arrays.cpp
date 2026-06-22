/*
 * Chapter 1 - Dynamically Allocated Arrays
 *
 * "new T[n]" allocates an array of n elements on the free store and returns a pointer to its
 * first element. Unlike a stack array, n can be a value computed at run time. Pair it with
 * "delete[] p;" to release the memory.
 *
 * Key notes:
 *   - The brackets in delete[] are essential. "delete p;" on a "new T[n]" pointer is
 *     undefined behavior.
 *   - Prefer std::vector for dynamic arrays - it tracks size, grows, and handles cleanup.
 *   - Prefer std::array or a stack array when the size is fixed at compile time.
 *   - Pointer arithmetic: "p + i" and "p[i]" both reach the i-th element. Out-of-bounds
 *     indexing is undefined behavior.
 *   - Since C++20 you can omit the array size with brace initialization:
 *         int* a = new int[] { 1, 2, 3, 4 };
 */

int main()
{
	int arraySize{ 8 };
	int* myVariableSizedArray{ new int[arraySize] };
	myVariableSizedArray[3] = 2;
	delete[] myVariableSizedArray;
	myVariableSizedArray = nullptr;
}
