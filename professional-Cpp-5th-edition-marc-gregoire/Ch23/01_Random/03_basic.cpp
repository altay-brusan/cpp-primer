/*
 * Chapter 23 - Engine plus Distribution: the Basic Recipe
 *
 * The canonical modern C++ way to generate a random number: combine an engine
 * with a distribution. A random_device produces a one-off seed, which
 * initializes an mt19937 Mersenne Twister engine (a fast, high-quality
 * pseudorandom generator). A uniform_int_distribution then maps the engine's
 * raw output into the desired range, here 1 to 99. Calling the distribution
 * with the engine as its argument yields one random number in that range.
 *
 * Key notes:
 *   - Engine and distribution are separate concerns: the engine supplies raw
 *     bits, the distribution shapes them into a range and shape.
 */

#include <print>
#include <random>

using namespace std;

int main()
{
	random_device seeder;
	mt19937 engine{ seeder() };

	uniform_int_distribution<int> distribution{ 1, 99 };
	println("{}", distribution(engine));
}

