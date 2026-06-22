/*
 * Chapter 23 - random_device (Hardware Entropy Source)
 *
 * Demonstrates std::random_device, the one engine in <random> that can produce
 * truly non-deterministic numbers from a hardware entropy source rather than a
 * mathematical formula. It needs no parameters: construct it, then call its
 * function-call operator to get a value, and query min(), max(), and entropy().
 * The entropy() method returns 0.0 when the implementation falls back to a
 * software pseudorandom generator and a non-zero estimate when real hardware
 * entropy is available.
 *
 * Key notes:
 *   - random_device is usually slower than a pseudorandom engine, so the common
 *     pattern is to use it only to seed a fast engine such as mt19937.
 */

#include <print>
#include <random>

using namespace std;

int main()
{
	random_device rnd;
	println("Entropy: {}", rnd.entropy());
	println("Min value: {}, Max value: {}", rnd.min(), rnd.max());
	println("Random number: {}", rnd());
}
