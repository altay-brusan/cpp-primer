/*
 * Chapter 27 - Atomic Operations: fetch_add()
 *
 * fetch_add() atomically adds a value to an atomic and returns the original
 * (pre-addition) value. Here an atomic<int> starts at 10; fetch_add(4) returns 10 (the
 * old value) and leaves the atomic holding 14, all as one uninterruptible transaction.
 */

#include <print>
#include <atomic>

using namespace std;

int main()
{
	atomic<int> value{ 10 };
	println("Value = {}", value.load());
	int fetched{ value.fetch_add(4) };
	println("Fetched = {}", fetched);
	println("Value = {}", value.load());
}
