/*
 * Chapter 13 - Handling Input Errors
 *
 * The canonical loop for robustly reading from an input stream. It sums numbers
 * from cin until end-of-file, distinguishing the three stream states after each
 * read: good() (success), eof() (clean end, stop), and fail() (bad token).
 * On failure it calls clear() to reset the error state, consumes the offending
 * token, warns, and continues.
 *
 * Key notes:
 *   - End-of-file is entered at the console with Control+Z then Enter on
 *     Windows (Control+D on Unix/Linux).
 *   - good() == (!fail() && !eof()); both good() and fail() are false at EOF.
 */

#include <iostream>
#include <print>
#include <string>

using namespace std;

int main()
{
	println("Enter numbers on separate lines to add.");
	println("Use Control+D followed by Enter to finish (Control+Z in Windows).");
	int sum{ 0 };

	if (!cin.good()) {
		println(cerr, "Standard input is in a bad state!");
		return 1;
	}

	while (!cin.bad()) {
		int number;
		cin >> number;
		if (cin.good()) {
			sum += number;
		} else if (cin.eof()) {
			break; // Reached end-of-file.
		} else if (cin.fail()) {
			// Failure!
			cin.clear(); // Clear the failure state.
			string badToken;
			cin >> badToken; // Consume the bad input.
			println(cerr, "WARNING: Bad input encountered: {}", badToken);
		}
	}

	println("The sum is {}.", sum);
}
