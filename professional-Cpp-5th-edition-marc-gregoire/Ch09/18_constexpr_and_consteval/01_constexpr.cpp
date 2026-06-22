/*
 * Chapter 9 - constexpr Functions
 *
 * A `constexpr` function MAY be evaluated at compile time when its arguments are
 * compile-time constants. If the arguments are runtime values - or if the result
 * is assigned to a non-constexpr variable - the same body runs at runtime instead.
 * `constexpr` is therefore a permission, not a requirement.
 *
 * Key notes:
 *   - When you initialize a `constexpr` variable from the result, the call MUST be
 *     evaluable at compile time. If the body would hit a runtime-only operation
 *     (like calling `log()` here when `someFlag` is true), the compile fails.
 *   - `const auto value3{ computeSomething(true) };` works because `value3` is
 *     not constexpr - the function is allowed to run at runtime in that case.
 *   - Array sizes like `int myArray[getArraySize()];` need a constant expression.
 *     `getArraySize()` qualifies because it is `constexpr` and called with no
 *     runtime inputs.
 *   - C++20 broadens what `constexpr` functions may contain (try/catch, virtual
 *     calls, dynamic allocations with `new`/`delete`, even `std::vector` in C++20).
 *   - Branches not taken in a `constexpr` evaluation do not have to be
 *     constant-evaluable - the compiler only checks what is reached.
 */
#include <print>
#include <string_view>

using namespace std;

constexpr int getArraySize()
{
	return 32;
}


void log(string_view message)
{
	print("{}", message);
}

constexpr int computeSomething(bool someFlag)
{
	if (someFlag)
	{
		log("someFlag is true");
		return 42;
	}
	else
	{
		return 84;
	}
}


int main()
{
	{
		int myArray[getArraySize()];	 // OK
		println("Size of array = {}", size(myArray));
	}

	{
		int myArray[getArraySize() + 1]; // OK
		println("Size of array = {}", size(myArray));
	}

	{
		constexpr auto value1{ computeSomething(false) };
		//constexpr auto value2{ computeSomething(true) }; // Error: doesn't compile!
		const auto value3{ computeSomething(true) };
	}
}
