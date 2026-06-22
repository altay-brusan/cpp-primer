/*
 * Chapter 32 - Reading an Entire File with istreambuf_iterator (syntax refresher)
 *
 * Another way to slurp an entire file into a std::string: construct the string from a
 * pair of istreambuf_iterator<char> objects. The first iterator is bound to the input
 * stream and the default-constructed second iterator acts as the end-of-stream sentinel,
 * so the range covers every character in the file (including whitespace).
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

	string fileContents{
		istreambuf_iterator<char> { inputFile },
		istreambuf_iterator<char> { }
	};
	println("{}", fileContents);
}
