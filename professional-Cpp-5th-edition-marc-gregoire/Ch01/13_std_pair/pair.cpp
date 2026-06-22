/*
 * Chapter 1 - std::pair
 *
 * std::pair<T1, T2> (in <utility>) packages two values of possibly different types into one
 * object. The values live as public data members named .first and .second.
 *
 * Key notes:
 *   - Construct with braces: "std::pair<int, std::string> p { 1, \"hi\" };". With CTAD the
 *     types are deduced: "std::pair p { 1, \"hi\" };".
 *   - std::make_pair(a, b) builds a pair without spelling the types; useful in templates.
 *   - Structured bindings decompose neatly: "auto [k, v] = p;".
 *   - std::map and std::unordered_map yield pair<const Key, Value> from their iterators - the
 *     same .first/.second idiom applies.
 *   - For more than two values, use std::tuple from <tuple>.
 */

#include <print>
#include <utility>

using namespace std;

int main()
{
	pair<double, int> myPair{ 1.23, 5 };
	// pair myPair { 1.23, 5 };  // Using CTAD
	println("{} {}", myPair.first, myPair.second);
}
