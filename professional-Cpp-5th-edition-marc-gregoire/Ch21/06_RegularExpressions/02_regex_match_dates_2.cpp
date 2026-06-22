/*
 * Chapter 21 - regex_match with Capture Groups (smatch)
 *
 * Extends the date validator by wrapping the year, month, and day subexpressions in
 * capture groups (parentheses) and passing an std::smatch object to regex_match().
 * When the match succeeds, the smatch is filled in: element [0] is the whole match,
 * and [1], [2], [3] are the year, month, and day capture groups, which are converted
 * to integers with stoi() and printed.
 *
 * Key notes:
 *   - smatch is match_results over string iterators; m[i] yields a sub_match whose
 *     str() returns the captured text.
 */

#include <print>
#include <regex>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	regex r{ "(\\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1])" };
	while (true) {
		print("Enter a date (year/month/day) (q=quit): ");
		string str;
		if (!getline(cin, str) || str == "q") {
			break;
		}

		if (smatch m; regex_match(str, m, r)) {
			int year{ stoi(m[1]) };
			int month{ stoi(m[2]) };
			int day{ stoi(m[3]) };
			println("  Valid date: Year={}, month={}, day={}", year, month, day);
		} else {
			println("  Invalid date!");
		}
	}
}