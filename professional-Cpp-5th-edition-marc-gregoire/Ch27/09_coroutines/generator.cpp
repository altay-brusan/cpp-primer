/*
 * Chapter 27 - Coroutines: a std::generator
 *
 * Coroutines are resumable functions: they can suspend with co_yield, return a value to
 * the caller, and resume where they left off. getSequenceGenerator() is a coroutine
 * returning a std::generator<int> (C++23) that lazily produces a sequence of values, one
 * per co_yield. The range-based for loop in main() drives it, resuming the coroutine each
 * iteration; the printed timestamps show that each value is computed on demand, not all
 * up front.
 *
 * Key notes:
 *   - Interactive: the loop calls cin.ignore(), waiting for the user to press Enter
 *     before requesting each next value.
 *   - Requires a compiler and library with C++23 <generator> support.
 */

#include <print>
#include <iostream>
#include <chrono>
#include <generator>

using namespace std;
using namespace std::chrono;

generator<int> getSequenceGenerator(int startValue, int numberOfValues)
{
	for (int i{ startValue }; i < startValue + numberOfValues; ++i) {
		// Print the local time to standard out, see Chapter 22.
		auto currentTime{ system_clock::now() };
		auto localTime{ current_zone()->to_local(currentTime) };
		print("{:%H:%M:%OS}: ", localTime);

		// Yield a value to the caller, and suspend the coroutine.
		co_yield i;
	}
}

int main()
{
	auto gen{ getSequenceGenerator(10, 5) };
	for (const auto& value : gen) {
		print("{} (Press enter for next value)", value);
		cin.ignore();
	}
}
