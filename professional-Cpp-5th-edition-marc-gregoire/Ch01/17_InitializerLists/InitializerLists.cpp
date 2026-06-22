/*
 * Chapter 1 - Initializer Lists
 *
 * std::initializer_list<T> (in <initializer_list>) lets a function accept a variable number
 * of values of the same type via a braced list at the call site. The function can then
 * iterate over the list with a range-based for.
 *
 * Key notes:
 *   - All elements in the braced list must convert to T - this is enforced at compile time.
 *     "sum({ 1, 2, 3.0 })" is rejected when T is int.
 *   - initializer_list is lightweight (a pointer to a contiguous read-only array plus a
 *     size). It does not own its elements; do not store one beyond the call.
 *   - Many Standard Library types accept an initializer_list constructor:
 *     "std::vector<int> v { 1, 2, 3 };".
 *   - auto with copy-list init deduces initializer_list: "auto a = { 1, 2 };" is
 *     std::initializer_list<int>. Direct-list init "auto b { 1 };" deduces int instead - and
 *     "auto b { 1, 2 };" is an error (C++17).
 *   - For heterogeneous variadic arguments, reach for variadic templates (Chapter 26)
 *     instead.
 */

#include <print>
#include <initializer_list>

using namespace std;

int sum(initializer_list<int> values)
{
	int total{ 0 };
	for (int value : values) {
		total += value;
	}
	return total;
}

int main()
{
	int a{ sum({ 1, 2, 3 }) };
	int b{ sum({ 10, 20, 30, 40, 50, 60 }) };

	println("{}", a);
	println("{}", b);

	//int c{ sum({ 1, 2, 3.0 }) }; // Error
}
