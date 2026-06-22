/*
 * Chapter 12 - Function Templates (1/2): A Generic Find
 *
 * Two overloads of Find:
 *   - `Find(value, arr, size)` - explicit size, works on any pointer.
 *   - `Find(value, arr)` with `T(&arr)[N]` - takes a reference to a C
 *     array, lets the compiler deduce N. The body just forwards to the
 *     pointer/size version.
 *
 * Highlights:
 *   - Template argument deduction: `Find(myInt, intArray, sz)` deduces
 *     `T = int` from the first argument's type.
 *   - Explicit form: `Find<double>(myInt, doubleArray, sz)` forces T to be
 *     double even when the first argument is int (an implicit conversion
 *     happens at the call).
 *   - The commented `Find(myInt, doubleArray, ...)` line shows what
 *     deduction can't do: it sees `T=int` from the value and `T=double`
 *     from the array - inconsistent, so it refuses to pick one.
 *
 * The function works for built-in types AND for any user type with
 * `operator==`. SpreadsheetCell has it (from the defaulted `<=>`), so it
 * fits in the same template.
 */
#include "SpreadsheetCell.h"
#include <print>
#include <optional>
#include <cstddef>

using namespace std;

template <typename T>
optional<size_t> Find(const T& value, const T* arr, size_t size)
{
	for (size_t i{ 0 }; i < size; ++i) {
		if (arr[i] == value) {
			return i; // Found it; return the index.
		}
	}
	return {}; // Failed to find it; return empty optional.
}

template <typename T, size_t N>
optional<size_t> Find(const T& value, const T(&arr)[N])
{
	return Find(value, arr, N);
}

int main()
{
	int myInt{ 3 }, intArray[]{ 1, 2, 3, 4 };
	const size_t sizeIntArray{ size(intArray) };

	optional<size_t> res;
	res = Find(myInt, intArray, sizeIntArray);        // calls Find<int> by deduction.
	res = Find<int>(myInt, intArray, sizeIntArray);   // calls Find<int> explicitly.
	if (res) { println("{}", *res); }
	else { println("Not found"); }

	double myDouble{ 5.6 }, doubleArray[]{ 1.2, 3.4, 5.7, 7.5 };
	const size_t sizeDoubleArray{ size(doubleArray) };

	res = Find(myDouble, doubleArray, sizeDoubleArray);         // calls Find<double> by deduction.
	res = Find<double>(myDouble, doubleArray, sizeDoubleArray); // calls Find<double> explicitly.
	if (res) { println("{}", *res); }
	else { println("Not found"); }

	//res = Find(myInt, doubleArray, sizeDoubleArray);        // DOES NOT COMPILE! Arguments are different types.
	res = Find<double>(myInt, doubleArray, sizeDoubleArray);  // calls Find<double> explicitly, even with myInt.

	SpreadsheetCell cell1{ 10 };
	SpreadsheetCell cellArray[]{ SpreadsheetCell{ 4 }, SpreadsheetCell{ 10 } };
	const size_t sizeCellArray{ size(cellArray) };

	res = Find(cell1, cellArray, sizeCellArray);                  // calls Find<SpreadsheetCell> by deduction.
	res = Find<SpreadsheetCell>(cell1, cellArray, sizeCellArray); // calls Find<SpreadsheetCell> explicitly.

	res = Find(myInt, intArray);
}
