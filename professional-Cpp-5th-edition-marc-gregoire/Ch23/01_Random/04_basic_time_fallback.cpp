/*
 * Chapter 23 - Seeding with a Time-Based Fallback
 *
 * A refinement of the basic engine-plus-distribution recipe that hardens the
 * seeding step. Because random_device may have no real entropy on some systems,
 * this sample checks seeder.entropy(): if it is non-zero the random_device is
 * used to produce the seed, otherwise it falls back to the current system time
 * from <ctime>. The chosen seed initializes the mt19937 engine, and a
 * uniform_int_distribution then produces a value in the range 1 to 99.
 *
 * Key notes:
 *   - The seed is cast to mt19937::result_type because random_device and
 *     time() yield different types than the engine expects.
 */

#include <print>
#include <random>
#include <ctime>

using namespace std;

int main()
{
	random_device seeder;

	const auto seed{ seeder.entropy() ? seeder() : time(nullptr) };

	mt19937 engine{ static_cast<mt19937::result_type>(seed) };

	uniform_int_distribution<int> distribution{ 1, 99 };
	println("{}", distribution(engine));
}

