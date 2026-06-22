/*
 * Chapter 13 - String Streams: Building a String with ostringstream
 *
 * String streams apply the stream metaphor to in-memory text. This sample reads
 * tokens from cin and writes them into an std::ostringstream (the 'o' is for
 * output), then retrieves the accumulated text with str(). Reading stops on the
 * token "done" or on end-of-file.
 *
 * Key notes:
 *   - Building a string by streaming into an ostringstream is more efficient
 *     than repeatedly concatenating std::string objects.
 */

#include <print>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
	println("Enter tokens. "
		"Control+D (Unix) or Control+Z (Windows) followed by Enter to end.");

	ostringstream outStream;

	bool firstLoop{ true };
	while (cin) {
		string nextToken;
		print("Next token: ");
		cin >> nextToken;

		if (!cin || nextToken == "done") {
			break;
		}

		if (!firstLoop) {
			outStream << ", ";
		}
		outStream << '"' << nextToken << '"';
		firstLoop = false;
	}

	println("The end result is: {}", outStream.str());
}
