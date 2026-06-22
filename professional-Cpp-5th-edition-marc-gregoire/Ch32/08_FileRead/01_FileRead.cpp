/*
 * Chapter 32 - Reading from a File, Token by Token (syntax refresher)
 *
 * Reads the FileWrite.out file produced by the 07_FileWrite sample using std::ifstream
 * and the stream extraction operator. The while loop "while (inputFile >> nextToken)"
 * reads one whitespace-delimited token at a time until extraction fails (end of file).
 *
 * Key notes:
 *   - This program expects FileWrite.out to already exist in the working directory.
 */
#include <print>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream inputFile{ "FileWrite.out" };
	if (inputFile.fail()) {
		println(cerr, "Unable to open file for reading.");
		return 1;
	}

	string nextToken;
	while (inputFile >> nextToken) {
		println("Token: {}", nextToken);
	}
}
