/*
 * Chapter 14 - Wrong catch Ordering: Base Class First (Bug)
 *
 * The buggy counterpart to 03: the catch for the base class exception is listed
 * before the catch for the derived invalid_argument. Because clauses match in
 * order, the base handler catches everything and the derived handler is dead
 * code that can never run. Always list catch clauses from most to least derived.
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
	} catch (const exception& e) { // BUG: catching base class first!
		println(cerr, "{}", e.what());
		return 1;
	} catch (const invalid_argument& /* e */) {
		// Take some special action for invalid filenames.
	}

	println("{} ", myInts);
}
