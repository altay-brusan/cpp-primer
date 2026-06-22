/*
 * Chapter 14 - Catching Polymorphically Through the Base Class
 *
 * readIntegerFile() throws invalid_argument or runtime_error, but because both
 * derive from std::exception, main() can handle them with one
 * catch (const exception& e) clause. A catch for a base-class reference matches
 * any derived exception. The book notes the trade-off: the higher in the
 * hierarchy you catch, the less specific your handling can be.
 */

#include <print>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <exception>
#include <format>

using namespace std;

vector<int> readIntegerFile(const string& filename)
{
	ifstream inputStream { filename };
	if (inputStream.fail()) {
		// We failed to open the file: throw an exception.
		const string error{ format("Unable to open file {}.", filename) };
		throw invalid_argument{ error };
	}

	// Read the integers one-by-one and add them to a vector.
	vector<int> integers;
	int temp;
	while (inputStream >> temp) {
		integers.push_back(temp);
	}

	if (!inputStream.eof()) {
		// We did not reach the end-of-file.
		// This means that some error occurred while reading the file.
		// Throw an exception.
		const string error{ format("Unable to read file {}.", filename) };
		throw runtime_error{ error };
	}

	return integers;
}

int main()
{
	const string filename{ "IntegerFile.txt" };
	vector<int> myInts;

	try {
		myInts = readIntegerFile(filename);
	} catch (const exception& e) {
		println(cerr, "{}", e.what());
		return 1;
	}

	println("{} ", myInts);
}
