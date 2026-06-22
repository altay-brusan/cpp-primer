/*
 * Chapter 20 - Specialized Searchers (Boyer-Moore)
 *
 * Demonstrates the C++17 searcher overload of std::search(). A
 * boyer_moore_searcher (from <functional>) is built from the needle ("needle")
 * and passed to search() to locate it inside a larger haystack string. The
 * Boyer-Moore algorithm is sublinear in practice because it can skip characters,
 * making it much faster than the default searcher for substring search.
 *
 * Key notes:
 *   - Alternatives are default_searcher and boyer_moore_horspool_searcher.
 */

#include <print>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

int main()
{
	// Boyer-Moore searcher
	string text{ "This is the haystack to search a needle in." };
	string toSearchFor{ "needle" };
	boyer_moore_searcher searcher{ cbegin(toSearchFor), cend(toSearchFor) };
	auto result{ search(cbegin(text), cend(text), searcher) };
	if (result != cend(text)) {
		println("Found the needle.");
	} else {
		println("Needle not found.");
	}
}
