/*
 * Chapter 23 - Visualizing a Normal Distribution
 *
 * The histogram sample from 07_uniform_int_distribution.cpp adapted to use a
 * normal_distribution (mean 50, standard deviation 10) instead of a uniform one.
 * Because a normal distribution works with doubles, each generated value is cast
 * to int before being tallied. One million samples are counted into a map and
 * written to res.csv. Plotting the file shows the characteristic bell curve:
 * values cluster near the center (50) and taper off toward the edges.
 *
 * Key notes:
 *   - Only two things change from the uniform version: the distribution type and
 *     the static_cast<int> on the generated value.
 *   - This program produces no console output; its result is the res.csv file.
 */

#include <random>
#include <map>
#include <fstream>
#include <functional>

using namespace std;

int main()
{
	const unsigned int Start{ 1 };
	const unsigned int End{ 99 };
	const unsigned int Iterations{ 1'000'000 };

	// Normal distributed Mersenne Twister.
	random_device seeder;
	mt19937 engine{ seeder() };
	normal_distribution<double> distribution{ 50, 10 };
	auto generator{ bind(distribution, engine) };
	map<int, int> histogram;
	for (unsigned int i{ 0 }; i < Iterations; ++i) {
		int randomNumber{ static_cast<int>(generator()) };
		// Search map for a key=randomNumber. If found, add 1 to the value associated
		// with that key. If not found, add the key to the map with value 1.
		++(histogram[randomNumber]);
	}

	// Write to a CSV file.
	ofstream of{ "res.csv" };
	for (unsigned int i{ Start }; i <= End; ++i) {
		of << i << ";" << histogram[i] << endl;
	}
}
