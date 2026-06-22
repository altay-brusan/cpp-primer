/*
 * Chapter 20 - Constrained Algorithms: ranges::generate
 *
 * Demonstrates std::ranges::generate() called on a whole container. A stateful
 * mutable lambda yields consecutive numbers. The first block passes the lambda by
 * value, so the algorithm's copy advances independently of the original; the
 * second wraps it in std::ref(), so the algorithm and later calls share one
 * counter.
 */

#include <print>
#include <vector>
#include <algorithm>
#include <ranges>

using namespace std;

int main()
{
	{
		auto nextNumber{ [counter = 0] () mutable { return ++counter; } };

		vector<int> values(10);
		ranges::generate(values, nextNumber);
		println("Vector contains {:n}", values);

		print("Four more next numbers: ");
		for (unsigned i{ 0 }; i < 4; ++i) {
			print("{}, ", nextNumber());
		}

		println("");
	}

	println("");

	// Passing a reference to the lambda expression.
	{
		auto nextNumber{ [counter = 0] () mutable { return ++counter; } };

		vector<int> values(10);
		ranges::generate(values, ref(nextNumber));
		println("Vector contains {:n}", values);

		print("Four more next numbers: ");
		for (unsigned i{ 0 }; i < 4; ++i) {
			print("{}, ", nextNumber());
		}

		println("");
	}
}