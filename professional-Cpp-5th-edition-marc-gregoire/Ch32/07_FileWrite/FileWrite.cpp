/*
 * Chapter 32 - Writing to a File (syntax refresher)
 *
 * Demonstrates basic file output with std::ofstream. The program opens FileWrite.out,
 * checks fail() to confirm the stream opened, writes a line, closes it, then reopens the
 * same file in append mode (ios_base::app) and adds a second line. The companion
 * 08_FileRead samples read the file this program produces.
 *
 * Key notes:
 *   - Always verify a stream opened (fail()) before relying on it.
 */
#include <print>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ofstream outputFile{ "FileWrite.out" };
	if (outputFile.fail()) {
		println(cerr, "Unable to open file for writing.");
		return 1;
	}
	outputFile << "Hello!" << endl;
	outputFile.close();

	ofstream appendFile{ "FileWrite.out", ios_base::app };
	if (appendFile.fail()) {
		println(cerr, "Unable to open file for appending.");
		return 2;
	}
	appendFile << "World!" << endl;
}
