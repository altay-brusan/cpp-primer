/*
 * Chapter 23 - Binding a Generator and Filling a Container
 *
 * Shows how to package an engine and a distribution into a single callable so
 * you no longer have to pass both each time. std::bind() (from <functional>)
 * binds the mt19937 engine as the argument of the uniform_int_distribution,
 * producing a zero-argument generator that returns a fresh random number on
 * each call. That generator is then handed to ranges::generate() to fill a
 * pre-sized vector of ten random values.
 *
 * Key notes:
 *   - generate() overwrites existing elements and does not insert, so the
 *     vector must already be sized to the count you want (here vector(10)).
 */

#include <print>
#include <random>
#include <vector>
#include <ranges>
#include <functional>

using namespace std;

int main()
{
	random_device seeder;
	mt19937 engine{ seeder() };
	uniform_int_distribution<int> distribution{ 1, 99 };

	auto generator{ bind(distribution, engine) };
	
	vector<int> values(10);
	ranges::generate(values, generator);
	
	println("{:n}", values);
}

