/*
 * Chapter 13 - Reading an Entire File into a String
 *
 * A handy idiom: open an ifstream and call std::getline() with '\0' as the
 * delimiter. Since a text file will not contain a null byte, getline() reads to
 * end-of-file, slurping the whole file into a single string in one call.
 *
 * Key notes:
 *   - Requires the data file some_data.txt to exist in the working directory;
 *     fail() is checked right after opening.
 */

#include <print>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	ifstream inputFile{ "some_data.txt" };
	if (inputFile.fail()) {
		println(cerr, "Unable to open file for reading.");
		return 1;
	}
	string fileContents;
	getline(inputFile, fileContents, '\0');
	println("\"{}\"", fileContents);
}
