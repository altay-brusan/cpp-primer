/*
 * Chapter 17 - Stream Buffer Iterator (istreambuf_iterator)
 *
 * Reads an entire file into a string using std::istreambuf_iterator<char>, which
 * iterates over the raw characters of a stream buffer rather than formatted values.
 * A begin iterator built from the ifstream and a default-constructed end iterator
 * are passed to the string constructor, slurping the whole file in one expression.
 * Unlike istream_iterator, istreambuf_iterator does no formatting and skips no
 * whitespace.
 *
 * Key notes:
 *   - Requires a data file named "some_data.txt" in the working directory; exits
 *     with code 1 if the file cannot be opened.
 */

#include <print>
#include <iterator>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream inputFile{ "some_data.txt" };
	if (inputFile.fail()) {
		println(cerr, "Unable to open file for reading.");
		return 1;
	}
	string fileContents{
		istreambuf_iterator<char>{ inputFile },
		istreambuf_iterator<char>{ }
	};
	println("{}", fileContents);
}
