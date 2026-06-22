/*
 * Chapter 20 - for_each Basics
 *
 * Demonstrates std::for_each(), which invokes a callback on every element of a
 * range. Here a generic lambda prints each key/value pair of a map; the element
 * type is const pair<int, int>&.
 *
 * Key notes:
 *   - A range-based for loop is often simpler than for_each() for this kind of task.
 */

#include <print>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
	map<int, int> myMap{ { 4, 40 }, { 5, 50 }, { 6, 60 } };
	for_each(cbegin(myMap), cend(myMap), [](const auto& p)
		{ println("{} -> {}", p.first, p.second); });
}
