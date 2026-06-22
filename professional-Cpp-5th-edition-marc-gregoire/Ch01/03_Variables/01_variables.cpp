// NOTE: Most compilers will issue a warning or an error
// when code is using uninitialized variables. Some compilers
// will generate code that will report an error at run time.

/*
 * Chapter 1 - Variables
 *
 * Variables in C++ are strongly typed and can be declared almost anywhere in a block, valid
 * from the point of declaration onward. A variable declared without an initializer holds
 * whatever bits were in that memory location - a classic source of bugs. Always give a
 * variable an initial value the moment you declare it.
 *
 * Key notes:
 *   - Uniform initialization (introduced in C++11) uses braces: int x { 7 };
 *     Prefer it over the older "int x = 7;" or "int x(7);" forms.
 *   - A pair of empty braces, {}, is a zero initializer: it zeroes primitives, sets pointers
 *     to nullptr, and default-constructs objects. Example: int n {}; gives n the value 0.
 *   - Uniform initialization also rejects narrowing conversions at compile time
 *     (e.g. int x { 3.14 }; is a compile error), unlike the assignment form.
 *   - Most compilers warn or error on use of uninitialized variables; some platforms even
 *     trap at run time.
 *
 * Example:
 *     int initializedInt { 7 };   // uniform init - preferred
 *     int legacyInt = 7;          // works, but does not catch narrowing
 */

#include <print>

using namespace std;

int main()
{
	int uninitializedInt;
	int initializedInt{ 7 };

	println("{} is a random value", uninitializedInt);
	println("{} was assigned as an initial value", initializedInt);
}
