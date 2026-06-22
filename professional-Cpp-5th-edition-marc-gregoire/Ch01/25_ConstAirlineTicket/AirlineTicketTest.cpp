/*
 * Driver for the const-qualified AirlineTicket - see AirlineTicket.h for the conceptual
 * notes on const methods.
 *
 * From the caller's point of view nothing changes: the same setters and getters are still
 * available. The difference is that this object could now be held through a const reference
 * or pointer and the inspectors would still be callable on it.
 */

#include "AirlineTicket.h"
#include <print>

using namespace std;

int main()
{
	AirlineTicket myTicket;  // Stack-based AirlineTicket
	myTicket.setPassengerName("Sherman T. Socketwrench");
	myTicket.setNumberOfMiles(700);
	double cost{ myTicket.calculatePriceInDollars() };
	println("This ticket will cost ${}", cost);
} 
