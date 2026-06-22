/*
 * Chapter 20 - The for_each_n Algorithm
 *
 * Demonstrates std::for_each_n(), which applies a callback to only the first n
 * elements of a range. It takes a begin iterator, the count, and the callback; the
 * example prints the first two entries of a map.
 *
 * Key notes:
 *   - for_each_n() performs no bounds checking, so n must not exceed the range.
 */

#include <print>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
	map<int, int> myMap{ { 4, 40 }, { 5, 50 }, { 6, 60 } };
	for_each_n(cbegin(myMap), 2, [](const auto& p)
		{ println("{} -> {}", p.first, p.second); });
}
