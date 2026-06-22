/*
 * Chapter 21 - regex_replace: One Word Per Line Without a Loop
 *
 * Uses std::regex_replace() to put each word of the input on its own line, without
 * writing any explicit loop over the matches. The pattern captures a run of word
 * characters, and the replacement is the captured word ($1) followed by a newline.
 * The format_no_copy flag drops the whitespace and other non-word characters from
 * the source so only the words, each on a new line, remain in the output.
 */

#include <print>
#include <regex>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	regex reg{ "([\\w]+)" };
	const string replacement{ "$1\n" };
	while (true) {
		print("Enter a string to split over multiple lines (q=quit): ");
		string str;
		if (!getline(cin, str) || str == "q") {
			break;
		}
		
		println("{}", regex_replace(str, reg, replacement,
			regex_constants::format_no_copy));
	}
}
