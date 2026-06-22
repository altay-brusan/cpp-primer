/*
 * Chapter 18 - const_iterator
 *
 * cbegin() and cend() return const_iterators, giving read-only access to
 * elements; with auto, this is how you force the iterator type to be const. A
 * const range-based for loop (const auto&) achieves the same read-only
 * traversal.
 */

#include <print>
#include <vector>
#include <string>

using namespace std;

int main()
{
	vector<string> stringVector(10, "hello");
	for (auto iter{ cbegin(stringVector) }; iter != cend(stringVector); ++iter) {
		println("{}", *iter);
	}
	
	for (const auto& element : stringVector) {
		println("{}", element);
	}
}
