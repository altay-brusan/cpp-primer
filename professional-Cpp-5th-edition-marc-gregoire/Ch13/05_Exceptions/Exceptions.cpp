/*
 * Chapter 13 - Handling Output Errors with Exceptions
 *
 * Instead of polling good()/bad()/fail() after each operation, a stream can be
 * told to throw on failure via exceptions(), passing the bits to watch
 * (failbit, badbit, eofbit). Failures then surface as ios_base::failure
 * exceptions, whose what() gives a description and code() the error code.
 *
 * Key notes:
 *   - How much useful detail what()/code() carry depends on the Standard
 *     Library implementation.
 */

#include <iostream>

using namespace std;

int main()
{
	cout.exceptions(ios::failbit | ios::badbit | ios::eofbit);
	try {
		cout << "Hello World." << endl;
	} catch (const ios_base::failure& ex) {
		cerr << "Caught exception: " << ex.what()
			<< ", error code = " << ex.code() << endl;
	}
}
