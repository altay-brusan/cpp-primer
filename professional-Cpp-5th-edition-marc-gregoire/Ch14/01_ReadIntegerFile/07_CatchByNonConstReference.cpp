/*
 * Chapter 14 - Catching an Exception by Reference-to-Non-const
 *
 * Shows the catch (exception& e) form. Catching by reference (unlike by value)
 * avoids slicing, but the book recommends reference-to-const since the handler
 * normally has no reason to modify the caught exception. Compare with
 * 06_CatchByValue.
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
	} catch (exception& /* e */) {
		println(cerr, "Unable to open file {}", filename);
		return 1;
	}

	println("{} ", myInts);
}
