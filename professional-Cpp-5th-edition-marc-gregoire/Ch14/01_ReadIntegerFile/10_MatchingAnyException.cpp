/*
 * Chapter 14 - Matching Any Exception with catch (...)
 *
 * readIntegerFile() throws either invalid_argument or runtime_error, but main()
 * collapses both into a single catch (...) handler, whose three dots are a
 * wildcard matching any exception type. Useful against poorly documented code,
 * but the book warns it handles every type identically and loses access to the
 * exception object, so prefer explicit, targeted handlers when you can.
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
	} catch (...) {
		println(cerr, "Error reading or opening file {}", filename);
		return 1;
	}

	println("{} ", myInts);
}
