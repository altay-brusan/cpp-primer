/*
 * Chapter 14 - Throwing and Catching Two Different Exception Types
 *
 * readIntegerFile() throws std::invalid_argument when the file cannot be opened
 * and std::runtime_error when reading fails. main() provides two catch clauses,
 * one per type, each returning a distinct exit code. The compiler matches the
 * thrown type to the appropriate handler.
 */

#include <print>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

vector<int> readIntegerFile(const string& filename)
{
	ifstream inputStream { filename };
	if (inputStream.fail()) {
		// We failed to open the file: throw an exception.
		throw invalid_argument{ "Unable to open the file." };
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
		throw runtime_error{ "Error reading the file." };
	}

	return integers;
}

int main()
{
	const string filename{ "IntegerFile.txt" };
	vector<int> myInts;

	try {
		myInts = readIntegerFile(filename);
	} catch (const invalid_argument& e) {
		println(cerr, "{}", e.what());
		return 1;
	} catch (const runtime_error& e) {
		println(cerr, "{}", e.what());
		return 2;
	}

	println("{} ", myInts);
}
