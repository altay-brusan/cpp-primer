/*
 * Chapter 32 - Throwing and Catching Exceptions (syntax refresher)
 *
 * A refresher on C++ exception syntax. throwIf() conditionally throws a standard
 * std::runtime_error, and main() wraps the calls in a try block that catches the
 * exception by const reference, prints e.what() to cerr, and returns a non-zero status.
 *
 * Key notes:
 *   - Catch exceptions by const reference to avoid slicing and unnecessary copies.
 */
#include <print>
#include <iostream>
#include <stdexcept>

using namespace std;

void throwIf(bool should)
{
	if (should) {
		throw runtime_error{ "Here's my exception" };
	}
}

int main()
{
	try {
		throwIf(false); // Doesn't throw.
		throwIf(true);  // Throws.
	} catch (const runtime_error& e) {
		println(cerr, "Caught exception: {}", e.what());
		return 1;
	}
}
