/*
 * Chapter 20 - Uniform Container Erasure (erase_if)
 *
 * Demonstrates the C++20 std::erase_if() free function, which removes all elements
 * matching a predicate directly from a container (here, empty strings from a
 * vector). Unlike the remove-erase idiom, it takes a container reference rather
 * than an iterator range and does the removal in a single call.
 *
 * Key notes:
 *   - The companion std::erase() removes by value; both are the preferred C++20
 *     way to delete elements from most containers.
 */

#include <print>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	vector<string> values{ "", "one", "", "two", "three", "four" };

	println("{:n}", values);
	erase_if(values, [](const string& str) { return str.empty(); });
	println("{:n}", values);
}
