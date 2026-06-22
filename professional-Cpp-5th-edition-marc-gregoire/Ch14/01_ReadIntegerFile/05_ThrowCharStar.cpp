/*
 * Chapter 14 - Throwing a const char* Exception
 *
 * Another non-object exception type: readIntegerFile() throws a C-style string
 * literal, which main() catches with catch (const char* e). Unlike a bare int,
 * the string can carry a description, but the book still recommends throwing
 * objects (standard or custom exception classes) so the type itself conveys
 * meaning.
 */

#include <print>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

vector<int> readIntegerFile(const string& filename)
{
	ifstream inputStream { filename };
	if (inputStream.fail()) {
		// We failed to open the file: throw an exception.
		throw "Unable to open file";
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
	} catch (const char* e) {
		println(cerr, "{}", e);
		return 1;
	}

	println("{} ", myInts);
}
