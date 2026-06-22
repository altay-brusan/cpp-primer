/*
 * Chapter 12 - Concepts (6/6): Constraint-Based Specialization
 *
 * Three pieces:
 *   - A generic `Find` template that uses `operator==`.
 *   - An `AreEqual` helper constrained to `std::floating_point` that
 *     compares using a tolerance based on `numeric_limits::epsilon`.
 *   - A second `Find` overload constrained to `std::floating_point T`
 *     that uses `AreEqual` instead of raw `==`.
 *
 * When you call `Find(5.7, doubleArray, sz)`, BOTH templates would be
 * candidates: the generic one fits everything, the floating-point one
 * fits doubles specifically. Subsumption picks the more constrained one,
 * so the float version runs and prints "floating_point version".
 *
 * For int arrays, only the generic Find is a candidate, so it runs and
 * prints "Generic version".
 *
 * Key notes:
 *   - This pattern replaces partial specialization for function templates
 *     (which C++ actually doesn't allow). Instead of specializing, you
 *     define a second overload with a stronger constraint and let
 *     subsumption pick the right one.
 *   - Floating-point equality with epsilon is one of those things that
 *     looks easy and is full of edge cases - subnormals, NaN, scaling.
 *     The body shown handles the common case; production code often
 *     reaches for a curated library function.
 */
#include <print>
#include <optional>
#include <cstddef>
#include <limits>
#include <concepts>
#include <cmath>

using namespace std;

template <typename T>
optional<size_t> Find(const T& value, const T* arr, size_t size)
{
	println("Generic version");
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

template <std::floating_point T>
bool AreEqual(T x, T y, int precision = 2)
{
	// Scale the machine epsilon to the magnitude of the given values and multiply
	// by the required precision.
	return fabs(x - y) <= numeric_limits<T>::epsilon() * fabs(x + y) * precision
		|| fabs(x - y) < numeric_limits<T>::min(); // The result is subnormal.
}

template <std::floating_point T>
optional<size_t> Find(const T& value, const T* arr, size_t size)
{
	println("floating_point version");
	for (size_t i{ 0 }; i < size; ++i) {
		if (AreEqual(arr[i], value)) {
			return i; // Found it; return the index.
		}
	}
	return {}; // Failed to find it; return empty optional.
}

int main()
{
	int myInt{ 3 }, intArray[]{ 1, 2, 3, 4 };
	const size_t sizeIntArray{ size(intArray) };

	optional<size_t> res;
	res = Find(myInt, intArray, sizeIntArray);        // calls Find<int> by deduction.
	res = Find<int>(myInt, intArray, sizeIntArray);   // calls Find<int> explicitly.
	res = Find(myInt, intArray);
	if (res) { println("{}", *res); }
	else { println("Not found"); }


	double myDouble{ 5.7 }, doubleArray[]{ 1.2, 3.4, 5.7, 7.5 };
	const size_t sizeDoubleArray{ size(doubleArray) };

	res = Find(myDouble, doubleArray, sizeDoubleArray);         // calls Find<double> by deduction.
	res = Find<double>(myDouble, doubleArray, sizeDoubleArray); // calls Find<double> explicitly.
	if (res) { println("{}", *res); }
	else { println("Not found"); }

	//res = Find(myInt, doubleArray, sizeDoubleArray);        // DOES NOT COMPILE! Arguments are different types.
	res = Find<double>(myInt, doubleArray, sizeDoubleArray);  // calls Find<double> explicitly, even with myInt.
}
