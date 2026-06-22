/*
 * Chapter 13 - Reading Multiple Values with >>
 *
 * A restaurant-reservation excerpt that reads several values of mixed types in
 * one chained cin expression: a guest name (string) and a party size (int).
 *
 * Key notes:
 *   - Because >> tokenizes on whitespace, a name with spaces cannot be entered
 *     here; the unget()/peek() samples later show solutions.
 *   - The opening prompt is not explicitly flushed, but appears anyway: reading
 *     from cin automatically flushes the tied cout buffer.
 */

#include <iostream>
#include <print>
#include <string>

using namespace std;

void getReservationData()
{
	string guestName;
	int partySize;
	print("Name and number of guests: ");
	cin >> guestName >> partySize;
	println("Thank you, {}.", guestName);
	if (partySize > 10) {
		println("An extra gratuity will apply.");
	}
}

int main()
{
	getReservationData();
}
