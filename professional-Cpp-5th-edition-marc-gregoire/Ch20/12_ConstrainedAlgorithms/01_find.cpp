/*
 * Chapter 20 - Constrained Algorithms: ranges::find
 *
 * Demonstrates the C++20 constrained algorithm std::ranges::find(). It can be
 * called like std::find() with a begin/end iterator pair, or more conveniently
 * with a single range argument. These ranges:: algorithms use concepts to
 * constrain their template parameters, giving clearer compiler errors.
 */

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>

using namespace std;

int main()
{
	vector values{ 1, 2, 3 };
	auto result1{ ranges::find(cbegin(values), cend(values), 2) };
	if (result1 != cend(values)) {
		println("{}", *result1);
	}

	auto result2{ ranges::find(values, 2) };
	if (result2 != cend(values)) {
		println("{}", *result2);
	}
}