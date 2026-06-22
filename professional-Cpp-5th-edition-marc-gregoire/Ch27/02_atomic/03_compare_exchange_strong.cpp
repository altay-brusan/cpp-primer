/*
 * Chapter 27 - Atomic Operations: compare_exchange_strong()
 *
 * compare_exchange_strong(expected, desired) atomically checks whether the atomic still
 * equals expected; if so it stores desired and returns true, otherwise it loads the
 * current value back into expected and returns false. This sample uses it in a retry
 * loop to multiply an atomic by a factor: it reads the value, computes the desired
 * product, and keeps retrying until the compare-and-swap succeeds. This is the
 * fundamental building block for lock-free data structures.
 */

#include <print>
#include <atomic>

using namespace std;

void atomicallyMultiply(atomic<int>& a, int n)
{
	int expected{ a.load() };
	int desired{ n * expected };
	while (!a.compare_exchange_strong(expected, desired)) {
		desired = n * expected;
	}
}

int main()
{
	atomic<int> value{ 10 };
	println("Value = {}", value.load());
	atomicallyMultiply(value, 3);
	println("Result = {}", value.load());
}
