/*
 * Chapter 21 - regex_match: Validating a Whole String
 *
 * Uses std::regex_match() to validate that user input is a date in year/month/day
 * form, where the year is four digits, the month is 1 to 12, and the day is 1 to 31.
 * regex_match() returns true only when the pattern matches the entire input string.
 * The pattern uses non-capturing groups written as (?: ... ) together with the
 * alternation operator and bounded repeats so the month and day ranges are enforced
 * without creating capture groups.
 *
 * Key notes:
 *   - The backslashes are doubled in the C++ string literal so the regex engine
 *     receives the digit shorthand correctly (the default grammar is ECMAScript).
 *   - It validates only the digit ranges, not real calendar limits (leap years etc.).
 */

#include <print>
#include <regex>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	regex r{ "\\d{4}/(?:0?[1-9]|1[0-2])/(?:0?[1-9]|[1-2][0-9]|3[0-1])" };
	while (true) {
		print("Enter a date (year/month/day) (q=quit): ");
		string str;
		if (!getline(cin, str) || str == "q") {
			break;
		}

		if (regex_match(str, r)) {
			println("  Valid date.");
		} else {
			println("  Invalid date!");
		}
	}
}
