/*
 * Chapter 1 - Using Classes (warm-up driver)
 *
 * Driver for the warm-up AirlineTicket class: build a stack-based instance, populate it
 * with the setters, ask the object for its price, and print the result.
 *
 * Key notes:
 *   - "AirlineTicket myTicket;" creates the object on the stack of main(). When main()
 *     returns, the object is destroyed automatically - no new/delete is needed.
 *   - Member access through "." (objects) or "->" (pointers).
 *   - The original sample uses "cout << ... << endl;"; later samples switch to std::println
 *     from <print> for cleaner formatting. Both forms produce equivalent output.
 *   - For heap allocation in real code, prefer smart pointers like std::make_unique<T>()
 *     instead of raw new (Chapter 7).
 */

#include <iostream>
#include "AirlineTicket.h"

using namespace std;

int main()
{
	AirlineTicket myTicket;  // Stack-based AirlineTicket
	myTicket.setPassengerName("Sherman T. Socketwrench");
	myTicket.setNumberOfMiles(700);
	double cost{ myTicket.calculatePriceInDollars() };
	cout << "This ticket will cost $" << cost << endl;
} 
