/*
 * Chapter 19 - Calling Member Functions with mem_fn
 *
 * Demonstrates std::mem_fn, which adapts a pointer to a member function into a callable
 * that can be passed to an algorithm. printMatchingStrings() takes a predicate; here
 * not_fn(mem_fn(&string::empty)) builds a callback that calls empty() on each string and
 * inverts the result, thereby printing only the non-empty strings.
 *
 * Key notes:
 *   - The &string:: qualification on &string::empty is required.
 *   - The book recommends a lambda over mem_fn for readability.
 */
#include <print>
#include <vector>
#include <string>
#include <functional>

using namespace std;

template<predicate<const string&> Matcher>
void printMatchingStrings(const vector<string>& strings, Matcher matcher)
{
	for (const auto& string : strings) {
		if (matcher(string)) {
			print("'{}' ", string);
		}
	}
}

int main()
{
	vector<string> values{ "Hello", "", "", "World", "!" };
	printMatchingStrings(values, not_fn(mem_fn(&string::empty)));
}
