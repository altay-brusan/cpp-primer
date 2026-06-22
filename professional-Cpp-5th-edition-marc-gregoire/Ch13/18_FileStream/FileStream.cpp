/*
 * Chapter 13 - File Streams: Writing to a File
 *
 * std::ofstream (from <fstream>) writes to a file using the same << operator as
 * cout. The only real difference from console streams is that the constructor
 * takes a filename and an open mode; here ios_base::trunc opens for output and
 * discards any existing contents. The program writes its own command-line
 * arguments to test.txt.
 *
 * Key notes:
 *   - No close() call is needed: the ofstream destructor closes the file.
 *   - An ofstream implicitly includes ios_base::out (ifstream implies in).
 */

#include <print>
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	ofstream outFile{ "test.txt", ios_base::trunc };
	if (!outFile.good()) {
		println(cerr, "Error while opening output file!");
		return -1;
	}
	outFile << "There were " << argc << " arguments to this program." << endl;
	outFile << "They are: " << endl;
	for (int i{ 0 }; i < argc; i++) {
		outFile << argv[i] << endl;
	}
}
