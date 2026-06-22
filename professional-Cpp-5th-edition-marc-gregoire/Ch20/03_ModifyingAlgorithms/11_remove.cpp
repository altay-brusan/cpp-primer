/*
 * Chapter 20 - The remove-erase Idiom
 *
 * Demonstrates the classic remove-erase idiom for deleting elements before C++20's
 * erase_if(). std::remove_if() cannot shrink the container; it shifts the kept
 * elements toward the front (via move assignment) and returns an iterator to the
 * start of the leftover tail, which is then passed to the container's erase() to
 * actually remove those elements. A second function shows the slower, error-prone
 * hand-written erase loop for comparison.
 *
 * Key notes:
 *   - Do not forget erase()'s second argument, or only one element is removed.
 */

#include <print>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void removeEmptyStrings(vector<string>& strings)
{
	auto it{ remove_if(begin(strings), end(strings),
		[](const string& str) { return str.empty(); }) };
	// Erase the removed elements.
	strings.erase(it, end(strings));
}

void removeEmptyStringsWithoutAlgorithms(vector<string>& strings)
{
	for (auto iter{ begin(strings) }; iter != end(strings); ) {
		if (iter->empty()) {
			iter = strings.erase(iter);
		} else {
			++iter;
		}
	}
}

int main()
{
	vector<string> myVector{ "", "one", "", "two", "three", "four" };

	println("{:n}", myVector);
	removeEmptyStrings(myVector);
	println("{:n}", myVector);
}
