/*
 * Chapter 14 - readIntegerFile Without Error Handling
 *
 * The starting point for the chapter's running example: a readIntegerFile()
 * that opens a file, reads ints into a vector with the >> operator, and returns
 * them. It deliberately ignores every failure - a missing file or malformed data
 * just yields an empty or partial vector with no diagnostic. Subsequent samples
 * in this folder progressively add exception-based error handling.
 */

#include <print>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<int> readIntegerFile(const string& filename)
{
	ifstream inputStream { filename };

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
	vector<int> myInts{ readIntegerFile(filename) };
	println("{} ", myInts);
}
