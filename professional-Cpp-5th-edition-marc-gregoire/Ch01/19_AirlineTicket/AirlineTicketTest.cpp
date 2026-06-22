/*
 * Chapter 1 - Using Classes
 *
 * Driver that exercises the AirlineTicket class: build a stack-based instance, set a
 * passenger name and mileage through the setters, ask the object to calculate its price, and
 * print the result. Once a class is defined, using it feels just like using a built-in type.
 *
 * Key notes:
 *   - "AirlineTicket t;" calls the default constructor and lives on the stack; storage is
 *     freed automatically at the end of the enclosing scope.
 *   - Reach members through "." on an object and "->" through a pointer.
 *   - For heap allocation prefer smart pointers (Chapter 7): std::make_unique<AirlineTicket>().
 */

#include <print>
#include "AirlineTicket.h"

using namespace std;

int main()
{
	AirlineTicket myTicket;  // Stack-based AirlineTicket
	myTicket.setPassengerName("Sherman T. Socketwrench");
	myTicket.setNumberOfMiles(700);
	double cost{ myTicket.calculatePriceInDollars() };
	println("This ticket will cost ${}", cost);
} 
