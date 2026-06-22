/*
 * Chapter 13 - unget(): Pushing a Character Back
 *
 * unget() backs the stream up by one position, putting the last character read
 * back on the stream. This version of getReservationData() allows whitespace in
 * the name: it reads char by char (with noskipws so spaces are not skipped),
 * and when it hits a digit it unget()s that digit so the following >> can read
 * the party size as an int.
 *
 * Key notes:
 *   - unget() takes no argument (it restores the last char read); use fail() to
 *     check whether it succeeded (it can fail at the start of the stream).
 */

#include <iostream>
#include <print>
#include <string>
#include <cctype>

using namespace std;

void getReservationData()
{
	print("Name and number of guests: ");
	string guestName;
	int partySize{ 0 };
	// Read characters until we find a digit
	char ch;
	cin >> noskipws;
	while (cin >> ch) {
		if (isdigit(ch)) {
			cin.unget();
			if (cin.fail()) { println(cerr, "unget() failed."); }
			break;
		}
		guestName += ch;
	}
	// Read partySize, if the stream is not in error state
	if (cin) { cin >> partySize; }
	if (!cin) {
		println(cerr, "Error getting party size.");
		return;
	}

	println("Thank you '{}', party of {}.", guestName, partySize);
	if (partySize > 10) {
		println("An extra gratuity will apply.");
	}
}

int main()
{
	getReservationData();
}
