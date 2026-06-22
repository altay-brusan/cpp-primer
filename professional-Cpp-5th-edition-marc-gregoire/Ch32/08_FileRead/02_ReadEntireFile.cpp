/*
 * Chapter 32 - Reading an Entire File into a String (syntax refresher)
 *
 * Reads the whole FileWrite.out file into a single std::string in one call. Using
 * getline() with a delimiter of '\0' (a character not present in the text file) makes
 * getline() consume everything up to end of file, capturing the entire contents at once.
 *
 * Key notes:
 *   - This program expects FileWrite.out to already exist in the working directory.
 */
#include <print>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream inputFile{ "FileWrite.out" };
	if (inputFile.fail()) {
		println(cerr, "Unable to open file for reading.");
		return 1;
	}

	string fileContents;
	getline(inputFile, fileContents, '\0');
	println("{}", fileContents);
}
