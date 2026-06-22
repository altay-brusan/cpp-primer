/*
 * Chapter 14 - Throwing a std::exception on File-Open Failure
 *
 * readIntegerFile() now checks inputStream.fail() and throws a bare
 * std::exception (from <exception>) if the file cannot be opened. main() catches
 * it by const reference and reports the error, returning a nonzero exit code.
 * This is the first version that actually surfaces an error instead of silently
 * returning an empty vector.
 */

#include <print>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <exception>

using namespace std;

vector<int> readIntegerFile(const string& filename)
{
	ifstream inputStream { filename };
	if (inputStream.fail()) {
		// We failed to open the file: throw an exception.
		throw exception {};
	}

	// Read the integers one-by-one and add them to a vector.
	vector<int> integers;
	int temp;
	while (inputStream >> temp) {
		integers.push_back(temp);
	}
	return integers;
}

int main()
{
	const string filename{ "IntegerFile.txt" };
	vector<int> myInts;

	try {
		myInts = readIntegerFile(filename);
	} catch (const exception& /* e */) {
		println(cerr, "Unable to open file {}", filename);
		return 1;
	}

	println("{} ", myInts);
}
