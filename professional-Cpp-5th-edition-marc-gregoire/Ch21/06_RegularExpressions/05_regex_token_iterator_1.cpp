/*
 * Chapter 21 - regex_token_iterator: Default Submatch
 *
 * Rewrites the word-splitting example using std::sregex_token_iterator instead of a
 * regex_iterator. With no submatch index given, the token iterator defaults to
 * submatch 0, so it walks the full match of each occurrence of the word pattern.
 * Because each token is already a sub_match, the loop calls iter->str() directly
 * rather than indexing into a match_results.
 *
 * Key notes:
 *   - The end iterator is a default-constructed sregex_token_iterator.
 */

#include <print>
#include <regex>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	regex reg{ "[\\w]+" };
	while (true) {
		print("Enter a string to split (q=quit): ");
		string str;
		if (!getline(cin, str) || str == "q") {
			break;
		}
		
		const sregex_token_iterator end;
		for (sregex_token_iterator iter{ cbegin(str), cend(str), reg };
			iter != end; ++iter) {
			println("\"{}\"", iter->str());
		}
	}
}