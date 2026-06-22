/*
 * Chapter 13 - Bidirectional I/O with fstream
 *
 * std::fstream is a bidirectional stream (it derives from iostream, hence from
 * both istream and ostream), able to read and write the same file. changeNumber
 * ForID() scans an ID/phone-number file for a matching record, then switches
 * from reading to writing in place to overwrite the phone number.
 *
 * Key notes:
 *   - A bidirectional stream keeps separate read and write positions; before
 *     writing, the code seeks the put position to the get position with
 *     seekp(tellg()).
 *   - In-place editing only works when the replacement is the same size as the
 *     original data; otherwise it would overwrite the next record.
 *   - Requires a data.txt file to be present in the working directory.
 */

#include <print>
#include <fstream>
#include <string>
#include <string_view>
#include <iostream>

using namespace std;

// Returns false on error
bool changeNumberForID(const string& filename, int id, string_view newNumber);

int main()
{
	changeNumberForID("data.txt", 263, "415-555-3333");
}

bool changeNumberForID(const string& filename, int id, string_view newNumber)
{
	fstream ioData{ filename };
	if (!ioData) {
		println(cerr, "Error while opening file {}.", filename);
		return false;
	}

	// Loop until the end of file
	while (ioData) {
		// Read the next ID.
		int idRead;
		ioData >> idRead;
		if (!ioData) {
			break;
		}

		// Check to see if the current record is the one being changed.
		if (idRead == id) {
			// Seek the write position to the current read position.
			ioData.seekp(ioData.tellg());
			// Output a space, then the new number.
			ioData << " " << newNumber;
			break;
		}

		// Read the current number to advance the stream.
		string number;
		ioData >> number;
	}
	return true;
}