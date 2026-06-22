/*
 * Chapter 1 - Loops
 *
 * Four looping constructs cover almost every case:
 *   - while (cond) { ... }            : check first, body may run zero times.
 *   - do { ... } while (cond);        : body always runs at least once, then check.
 *   - for (init; cond; step) { ... }  : combine all three loop pieces on one line.
 *   - for (T x : range) { ... }       : range-based for, iterates a container's elements.
 *
 * Key notes:
 *   - break exits the nearest loop immediately. continue jumps to the next iteration. Both
 *     are fine; "continue" can hurt readability if used heavily.
 *   - In a range-based for, write "for (auto& x : c)" for in-place modification or to avoid
 *     copies. Use "for (const auto& x : c)" when you only read.
 *   - C++20 range-based for accepts an init-statement:
 *         for (auto arr = makeArray(); int i : arr) { ... }
 *     Variables introduced in the init-statement live only inside the loop.
 *   - The range-based for works for C arrays, std::initializer_list, and any type with
 *     begin()/end() returning iterators (i.e. all Standard Library containers).
 *   - Modifying the container being iterated may invalidate iterators - usually a bug.
 */

#include <print>
#include <array>

using namespace std;

int main()
{
	{
		// The while loop
		int i{ 0 };
		while (i < 5) {
			println("This is silly.");
			++i;
		}
	}

	println("");

	{
		// The do/while loop
		int i{ 100 };
		do {
			println("This is silly.");
			++i;
		} while (i < 5);
	}

	println("");

	{
		// The for loop
		for (int i{ 0 }; i < 5; ++i) {
			println("This is silly.");
		}
	}

	println("");

	{
		// The range-based for loop
		array arr{ 1, 2, 3, 4 };
		for (int i : arr) { println("{}", i); }
	}

	println("");

	{
		// The range-based for loop with initializer
		for (array arr{ 1, 2, 3, 4 }; int i : arr) { println("{}", i); }
	}
}