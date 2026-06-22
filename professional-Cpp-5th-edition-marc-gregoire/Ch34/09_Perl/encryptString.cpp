/*
 * Chapter 34 - C++ Program Driven by a Script via argv and Exit Code
 *
 * The C++ half of a script-plus-C++ pipeline: a companion Perl script scans a
 * log file and shells out to this program to encrypt each password. The built-in
 * interface to the scripting environment is simply main()'s command-line
 * arguments and return value. It reads the string from argv[1] (checking argc
 * first), writes the result to standard output for the script to capture, and
 * returns non-zero on misuse so the caller can detect failure. The "encryption"
 * here just shifts each character by 13 to keep the example simple.
 */

#include <print>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

string encrypt(string_view input);

int main(int argc, char** argv)
{
	if (argc < 2) {
		println(cerr, "Usage: {} string-to-be-encrypted", argv[0]);
		return 1;
	}

	print("{}", encrypt(argv[1]));
} 

// Performs a very weak form of "encryption" by 
// adding 13 to each character of the string.
string encrypt(string_view input)
{
	string encrypted{ input.data() };
	for (auto& character : encrypted) {
		character += 13;
	}
	return encrypted;
}
