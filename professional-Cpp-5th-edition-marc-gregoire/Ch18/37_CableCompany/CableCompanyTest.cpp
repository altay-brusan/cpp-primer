/*
 * Chapter 18 - CableCompany Demo
 *
 * Driver for the bitset-and-map cable example - see CableCompany.h for the
 * conceptual notes. Defines three packages, creates a customer on the basic
 * package, adds the sports package, prints the resulting channel bitset, and
 * shows an unknown customer triggering an exception.
 */

#include "CableCompany.h"
#include <print>
#include <stdexcept>

using namespace std;

int main()
{
	CableCompany myCC;
	myCC.addPackage("basic",   "1111000000");
	myCC.addPackage("premium", "1111111111");
	myCC.addPackage("sports",  "0000100111");

	myCC.newCustomer("Marc G.", "basic");
	myCC.addPackageToCustomer("Marc G.", "sports");
	println("{}", myCC.getCustomerChannels("Marc G.").to_string());

	try {
		println("{}", myCC.getCustomerChannels("John").to_string());
	} catch (const exception& e) {
		println("Error: {}", e.what());
	}
}
