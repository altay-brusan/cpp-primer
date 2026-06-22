/*
 * Chapter 23 - Visualizing a Uniform Distribution
 *
 * Generates one million random integers in the range 1 to 99 with a
 * uniform_int_distribution driven by an mt19937 engine, and tallies how often
 * each value appears in a histogram stored as a map. The counts are written to
 * a semicolon-separated res.csv file that can be opened in a spreadsheet to plot
 * the distribution. The resulting graph is roughly flat: every value occurs
 * about ten thousand times, illustrating what "uniform" means.
 *
 * Key notes:
 *   - This program produces no console output; its result is the res.csv file.
 *   - Compare with 08_normal_distribution.cpp, which differs only in the
 *     distribution used.
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

	// Uniform distributed Mersenne Twister.
	random_device seeder;
	mt19937 engine{ seeder() };
	uniform_int_distribution<int> distribution{ Start, End };
	auto generator{ bind(distribution, engine) };
	map<int, int> histogram;
	for (unsigned int i{ 0 }; i < Iterations; ++i) {
		int randomNumber{ generator() };
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
