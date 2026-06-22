/*
 * Chapter 20 - The shuffle Algorithm
 *
 * Demonstrates std::shuffle(), which randomly reorders the elements of a range in
 * linear time. It requires a uniform random number generator; here a
 * default_random_engine seeded from std::random_device drives six successive
 * shuffles of the same vector.
 */

#include <print>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

int main()
{
	vector values{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	random_device seeder;
	default_random_engine generator{ seeder() };

	for (int i{ 0 }; i < 6; ++i) {
		shuffle(begin(values), end(values), generator);
		println("{:n}", values);
	}
}
