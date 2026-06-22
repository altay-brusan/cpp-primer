/*
 * Chapter 14 - Throwing the Same Exception Type from Multiple Sites
 *
 * readIntegerFile() can now fail two ways - failing to open the file and failing
 * to read it - and throws a std::runtime_error (from <stdexcept>) in both cases,
 * each with its own descriptive message. main() needs only a single
 * catch (const exception&) since runtime_error derives from std::exception, and
 * it uses e.what() to distinguish which failure occurred.
 */

#include <print>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

vector<int> readIntegerFile(const string& filename)
{
	ifstream inputStream { filename };
	if (inputStream.fail()) {
		// We failed to open the file: throw an exception.
		throw runtime_error{ "Unable to open the file." };
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
	} catch (const exception& e) {
		println(cerr, "{}", e.what());
		return 1;
	}

	println("{} ", myInts);
}
