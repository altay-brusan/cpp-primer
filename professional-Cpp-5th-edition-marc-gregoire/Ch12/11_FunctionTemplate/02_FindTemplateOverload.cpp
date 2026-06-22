/*
 * Chapter 12 - Function Templates (2/2): Overloading the Template
 *
 * Same Find function as the previous sample, plus a *non-template*
 * overload for `const char*` that uses `strcmp` for the comparison. The
 * compiler always prefers a non-template function over a template when
 * both are equally good candidates - that's why `Find(word, words, ...)`
 * prints "overload".
 *
 * Forcing the template anyway: `Find<const char*>(...)` skips the
 * non-template overload because the explicit template arguments make the
 * template the only candidate at the call site.
 *
 * Key notes:
 *   - This is one of the very few places where you mix a hand-written
 *     overload with a template. Most of the time `if constexpr` or a
 *     specialization is cleaner.
 *   - The comment about `const char word[]` is real: string-literal
 *     pooling can make pointer comparison succeed by accident. Putting
 *     "two" in a local array guarantees its address differs from the
 *     literal in the `words` array.
 */
#include "SpreadsheetCell.h"
#include <print>
#include <optional>
#include <cstddef>
#include <cstring>

using namespace std;

template <typename T>
optional<size_t> Find(const T& value, const T* arr, size_t size)
{
	println("original");
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

optional<size_t> Find(const char* value, const char** arr, size_t size)
{
	println("overload");
	for (size_t i{ 0 }; i < size; ++i) {
		if (strcmp(arr[i], value) == 0) {
			return i; // Found it; return the index.
		}
	}
	return {}; // Failed to find it; return empty optional.
}

int main()
{
	// Using an array for word to make sure no literal pooling happens, see Chapter 2.
	const char word[]{ "two" };
	const char* words[]{ "one", "two", "three", "four" };
	const size_t sizeWords{ size(words) };
	optional<size_t> res{ Find(word, words, sizeWords) }; // Calls non-template find.
	if (res) { println("{}", *res); }
	else { println("Not found"); }

	res = Find<const char*>(word, words, sizeWords); // Calls template with T=const char*.
	if (res) { println("{}", *res); }
	else { println("Not found"); }
}
