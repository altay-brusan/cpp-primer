/*
 * Chapter 13 - Jumping Around with seek() and tell()
 *
 * Demonstrates random access within a stream. It writes "54321" to test.out,
 * checks the write position with tellp(), seeks back to position 2 with
 * seekp(2, ios_base::beg), overwrites that byte with a 0, then reopens the file
 * for input and reads back 54021 to confirm.
 *
 * Key notes:
 *   - Output streams use seekp()/tellp() (p = put); input streams use
 *     seekg()/tellg() (g = get). Positions/offsets are measured in bytes.
 *   - Two-arg seek is relative to ios_base::beg, ios_base::end, or
 *     ios_base::cur.
 */

#include <print>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	ofstream fout{ "test.out" };
	if (!fout) {
		println(cerr, "Error opening test.out for writing.");
		return 1;
	}

	// 1. Output the string "54321".
	fout << "54321";

	// 2. Verify that the marker is at position 5.
	streampos curPos{ fout.tellp() };
	if (curPos == 5) {
		println("Test passed: Currently at position 5.");
	} else {
		println("Test failed: Not at position 5!");
	}

	// 3. Move to position 2 in the output stream.
	fout.seekp(2, ios_base::beg);

	// 4. Output a 0 in position 2 and close the output stream.
	fout << 0;
	fout.close();

	// 5. Open an input stream on test.out.
	ifstream fin{ "test.out"};
	if (!fin) {
		println(cerr, "Error opening test.out for reading.");
		return 1;
	}

	// 6. Read the first token as an integer.
	int testVal;
	fin >> testVal;
	if (!fin) {
		println(cerr,  "Error reading from file.");
		return 1;
	}

	// 7. Confirm that the value is 54021.
	const int expected{ 54021 };
	if (testVal == expected) {
		println("Test passed: Value is {}.", expected);
	} else {
		println("Test failed: Value is not {} (it was {}).", expected, testVal);
	}
}
