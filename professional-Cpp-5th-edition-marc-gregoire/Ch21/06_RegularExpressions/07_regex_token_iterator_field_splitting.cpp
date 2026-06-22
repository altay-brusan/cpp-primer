/*
 * Chapter 21 - regex_token_iterator: Field Splitting (Tokenization)
 *
 * Demonstrates tokenization mode of std::sregex_token_iterator, triggered by
 * passing a submatch index of -1. In this mode the iterator yields the substrings
 * that fall between matches, that is, the text that does NOT match the regex, making
 * it a safer, more flexible replacement for C's strtok(). The pattern (a raw string
 * literal) matches a comma or semicolon surrounded by optional whitespace, so the
 * input is split into trimmed fields. The fields are first printed inline and then
 * collected into a vector by constructing it from the iterator range.
 */

#include <print>
#include <regex>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	regex reg{ R"(\s*[,;]\s*)" };
	while (true) {
		print("Enter a string to split on ',' and ';' (q=quit): ");
		string str;
		if (!getline(cin, str) || str == "q") {
			break;
		}
		
		// Iterate over the tokens.
		const sregex_token_iterator end;
		for (sregex_token_iterator iter{ cbegin(str), cend(str), reg, -1 };
			iter != end; ++iter) {
			print("\"{}\", ", iter->str());
		}
		println("");

		// Store all tokens in a vector.
		vector<string> tokens {
			sregex_token_iterator { cbegin(str), cend(str), reg, -1 },
			sregex_token_iterator {} };
		// Print the contents of the tokens vector.
		println("{:n}", tokens);
	}
}