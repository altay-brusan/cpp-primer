/*
 * Chapter 18 - unordered_map
 *
 * unordered_map is a hash table mapping keys to values with average
 * constant-time lookup; unlike map it does not keep elements sorted. The
 * example builds one with uniform initialization and iterates it with C++23
 * range formatting, structured bindings, and plain .first and .second access.
 */

#include <print>
#include <unordered_map>
#include <string>

using namespace std;

int main()
{
	unordered_map<int, string> m{
		{1, "Item 1"},
		{2, "Item 2"},
		{3, "Item 3"},
		{4, "Item 4"},
	};

	// Using C++23 support for formatting/printing ranges.
	println("{}", m);

	// Using structured bindings.
	for (const auto&[key, value] : m) {
		print("{} = {}, ", key, value);
	}
	println("");

	// Without structured bindings.
	for (const auto& p : m) {
		print("{} = {}, ", p.first, p.second);
	}
	println("");
}
