/*
 * Chapter 21 - regex_iterator: Iterating Over All Matches
 *
 * Uses std::sregex_iterator to find every occurrence of a pattern in a source
 * string, which is the safe alternative to calling regex_search() in a loop. The
 * pattern matches runs of one or more word characters, so the loop extracts each
 * word and prints it in quotes. Dereferencing the iterator yields an smatch, and
 * element [0] of that smatch is the matched substring.
 *
 * Key notes:
 *   - The end iterator is a default-constructed sregex_iterator.
 *   - regex_iterator stores a pointer to the regex, so it cannot be constructed
 *     from a temporary regex object.
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
		
		const sregex_iterator end;
		for (sregex_iterator iter{ cbegin(str), cend(str), reg }; iter != end; ++iter) {
			println("\"{}\"", (*iter)[0].str());
		}
	}
}