/*
 * Chapter 23 - Passing a Generator to a Function
 *
 * Builds on the bound-generator idea by showing how to pass that generator into
 * a helper function even though its exact type is unknown. fillVector() uses the
 * C++20 abbreviated function template syntax (const auto and generator) to accept
 * any callable and forwards it to ranges::generate(). The commented-out
 * alternatives show the other two approaches: a constrained function template
 * and a std::function<int()> parameter.
 *
 * Key notes:
 *   - A bound generator has an unspecified type, so to pass it around you take
 *     it by template parameter (auto) or wrap it in std::function<int()>.
 */

#include <print>
#include <random>
#include <vector>
#include <ranges>
#include <functional>

using namespace std;

// Using the abbreviated function template syntax.
void fillVector(vector<int>& values, const auto& generator)
{
	ranges::generate(values, generator);
}

//template<invocable T>
//void fillVector(vector<int>& values, const T& generator)
//{
//	ranges::generate(values, generator);
//}

//void fillVector(vector<int>& values, const function<int()>& generator)
//{
//	ranges::generate(values, generator);
//}

int main()
{
	random_device seeder;
	mt19937 engine{ seeder() };
	uniform_int_distribution<int> distribution{ 1, 99 };

	auto generator{ bind(distribution, engine) };

	vector<int> values(10);
	fillVector(values, generator);

	println("{:n}", values);
}

