/*
 * Chapter 23 - The Old C-Style rand() and srand()
 *
 * Shows the pre-C++11 way of generating random numbers with the C library's
 * srand() and rand() from <cstdlib>. srand() seeds the global generator once
 * (here with the current time from <ctime>), after which rand() returns
 * pseudorandom values in the range 0 to RAND_MAX. The getRandom() helper maps
 * a value into [min, max] using the modulo trick. This style is discouraged in
 * modern C++ and is included only to contrast it with the <random> library.
 *
 * Key notes:
 *   - Seeding with the same value reproduces the same sequence; the system time
 *     is used so each run differs.
 *   - The 1UL avoids arithmetic overflow when max equals the maximum int.
 *   - The low-order bits of rand() are often weak, so modulo into a small range
 *     (such as 1 to 6) gives poor randomness; prefer the engines and
 *     distributions in <random> instead.
 */

#include <print>
#include <ctime>
#include <cstdlib>

using namespace std;

int getRandom(int min, int max)
{
	return static_cast<int>(rand() % (max + 1UL - min)) + min;
}

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	
	println("{}", rand());

	println("{}", getRandom(1, 6));
}
