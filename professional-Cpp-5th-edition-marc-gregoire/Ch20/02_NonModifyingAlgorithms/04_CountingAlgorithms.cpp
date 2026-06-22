/*
 * Chapter 20 - Counting Algorithms: all_of, any_of, none_of
 *
 * Demonstrates the three Boolean "quantifier" counting algorithms. all_of()
 * returns true when every element satisfies the predicate, any_of() when at least
 * one does, and none_of() when no element does. Each is applied with a lambda
 * predicate to a separate sample vector.
 */

#include <print>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	// all_of()
	vector vec2{ 1, 1, 1, 1 };
	if (all_of(cbegin(vec2), cend(vec2), [](int i){ return i == 1; })) {
		println("All elements are == 1");
	} else {
		println("Not all elements are == 1");
	}

	// any_of()
	vector vec3{ 0, 0, 1, 0 };
	if (any_of(cbegin(vec3), cend(vec3), [](int i){ return i == 1; })) {
		println("At least one element == 1");
	} else {
		println("No elements are == 1");
	}

	// none_of()
	vector vec4{ 0, 0, 0, 0 };
	if (none_of(cbegin(vec4), cend(vec4), [](int i){ return i == 1; })) {
		println("All elements are != 1");
	} else {
		println("Some elements are == 1");
	}
}
