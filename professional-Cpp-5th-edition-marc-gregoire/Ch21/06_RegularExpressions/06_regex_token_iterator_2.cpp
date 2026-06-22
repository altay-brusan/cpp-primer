/*
 * Chapter 21 - regex_token_iterator: Selecting Specific Capture Groups
 *
 * Uses std::sregex_token_iterator with an explicit list of submatch indices to
 * iterate over only chosen capture groups. The date pattern captures year, month,
 * and day, and a vector of indices {2, 3} tells the token iterator to visit just the
 * month and day groups of each match, printing only those two values for valid dates.
 *
 * Key notes:
 *   - The pattern adds the begin and end anchors so it matches the entire input,
 *     which regex_match did automatically but the iterators do not.
 */

#include <print>
#include <regex>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	regex reg{ "^(\\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1])$" };
	while (true) {
		print("Enter a date (year/month/day) (q=quit): ");
		string str;
		if (!getline(cin, str) || str == "q") {
			break;
		}

		vector indices{ 2, 3 };
		const sregex_token_iterator end;
		for (sregex_token_iterator iter{ cbegin(str), cend(str), reg, indices };
			iter != end; ++iter) {
			println("\"{}\"", iter->str());
		}
	}
}