/*
 * Chapter 13 - Linking Streams Together with tie()
 *
 * tie() establishes flush-on-access between streams: when data is requested from
 * an input stream, its tied output stream is flushed first. Here an ifstream on
 * input.txt is tied to an ofstream on output.txt, so reading from inFile forces
 * the unflushed "Hello there!" out to outFile. (This is the same mechanism that
 * links cin and cout.)
 *
 * Key notes:
 *   - Pass nullptr to tie() to break the link.
 */

#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream inFile{ "input.txt" };  // Note: input.txt must exist.
	ofstream outFile{ "output.txt" };
	// Set up a link between inFile and outFile.
	inFile.tie(&outFile);
	// Output some text to outFile. Normally, this would
	// not flush because std::endl is not send.
	outFile << "Hello there!";
	// outFile has NOT been flushed.
	// Read some text from inFile. This will trigger flush() on outFile.
	string nextToken;
	inFile >> nextToken;
	// outFile HAS been flushed.
}
