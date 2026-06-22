/*
 * Chapter 19 - std::invoke_r
 *
 * Demonstrates std::invoke_r (C++23), a variant of invoke that lets you specify the
 * desired return type explicitly. invoke(sum, 11, 22) yields an int (sum's natural return
 * type), while invoke_r<double>(sum, 11, 22) requests the result be converted to double.
 *
 * Key notes:
 *   - No console output; observe the deduced result types in a debugger.
 */
#include <print>
#include <functional>

using namespace std;

int sum(int a, int b)
{
	return a + b;
}

int main()
{
	auto res1{ invoke(sum, 11, 22) };           // Type of res1 is int.
	auto res2{ invoke_r<double>(sum, 11, 22) }; // Type of res2 is double.
}
