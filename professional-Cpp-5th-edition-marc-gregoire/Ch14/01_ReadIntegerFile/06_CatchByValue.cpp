/*
 * Chapter 14 - Catching an Exception by Value
 *
 * Shows the legal-but-discouraged catch (exception e) form, which catches the
 * exception object by value. Catching by value copies the object and risks
 * slicing when the thrown type derives from the caught type. The book's rule is
 * to always catch by reference-to-const instead; compare with
 * 07_CatchByNonConstReference and the by-const-reference forms used elsewhere.
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
	} catch (exception /* e */) {
		println(cerr, "Unable to open file {}", filename);
		return 1;
	}

	println("{} ", myInts);
}
