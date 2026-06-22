/*
 * Chapter 18 - map Uniform Initialization and Printing
 *
 * Builds a map<string, int> with uniform initialization from a braced list of
 * key/value pairs (the elements come out sorted by key) and prints it two ways:
 * iterating pairs via .first and .second, and with C++23 range formatting.
 */

#include <print>
#include <map>
#include <string>

using namespace std;

int main()
{
	map<string, int> m{
		{ "Marc G.", 12 },
		{ "Warren B.", 34 },
		{ "Peter V.W.", 56 }
	};

	for (const auto& p : m) {
		println("{} = {}", p.first, p.second);
	}

	println("");

	println("{}", m);
}
