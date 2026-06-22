/*
 * Chapter 13 - Flushing an Output Stream
 *
 * Output streams usually buffer (accumulate) data rather than writing it to the
 * destination immediately, since larger blocks are more performant. This sample
 * forces accumulated data out by calling flush() explicitly. A buffer is also
 * flushed automatically on endl, when the stream is destructed, when the buffer
 * fills, or when input is requested from a tied input stream.
 */

#include <iostream>

using namespace std;

int main()
{
	cout << "abc";
	cout.flush();    // abc is written to the console.
	cout << "def";
	cout << endl;    // def is written to the console.
}
