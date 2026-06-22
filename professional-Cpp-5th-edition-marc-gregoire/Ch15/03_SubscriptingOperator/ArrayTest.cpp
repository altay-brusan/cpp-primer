/*
 * Chapter 15 - Using the Subscripting Operator
 *
 * Driver that contrasts the verbose setElementAt()/getElementAt() interface with the
 * natural array[i] notation enabled by operator[]. printArray() takes the Array by
 * reference-to-const, which forces the const operator[] overload to be selected, while the
 * non-const code in main() uses the growing overload to assign elements.
 */
#include "Array.h"
#include <print>
#include <cstddef>

using namespace std;

void printArray(const Array<int>& arr)
{
	for (size_t i{ 0 }; i < arr.getSize(); ++i) {
		print("{} ", arr[i]); // Calls the const operator[] because arr is a const object.
	}
	println("");
}

int main()
{
	{
		Array<int> myArray;
		for (size_t i{ 0 }; i < 20; i += 2) {
			myArray.setElementAt(i, 100);
		}
		for (size_t i{ 0 }; i < 20; ++i) {
			print("{} ", myArray.getElementAt(i));
		}
		println("");
	}


	{
		Array<int> myArray;
		for (size_t i{ 0 }; i < 20; i += 2) {
			myArray[i] = 100;	// Calls the non-const operator[] because myArray is a non-const object.
		}
		for (size_t i{ 0 }; i < 20; ++i) {
			print("{} ", myArray[i]);
		}

		println("");

		printArray(myArray);
	}
}
