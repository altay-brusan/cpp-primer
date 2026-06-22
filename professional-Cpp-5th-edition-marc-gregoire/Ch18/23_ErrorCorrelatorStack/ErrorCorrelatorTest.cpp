/*
 * Chapter 18 - Error Correlator Demo (stack)
 *
 * Driver for the stack-based ErrorCorrelator - see ErrorCorrelator.h for the
 * conceptual notes. Adds three errors and drains them, showing LIFO order: the
 * last error added is processed first.
 */

#include "ErrorCorrelator.h"
#include <print>
#include <stdexcept>
#include <iostream>

using namespace std;

int main()
{
	ErrorCorrelator ec;

	ec.addError(Error{ 3, "Unable to read file" });
	ec.addError(Error{ 1, "Incorrect entry from user" });
	ec.addError(Error{ 10, "Unable to allocate memory!" });

	while (true) {
		try {
			Error e{ ec.getError() };
			cout << e << endl;
		} catch (const out_of_range&) {
			println("Finished processing errors");
			break;
		}
	}
}
