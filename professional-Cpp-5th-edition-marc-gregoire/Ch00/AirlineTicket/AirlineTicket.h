#pragma once

/*
 * Chapter 1 - Defining Classes (warm-up sample)
 *
 * This is the warm-up AirlineTicket class - the same one revisited later in Ch01/19 and
 * extended with const methods in Ch01/25. A class defines an object's data members and
 * methods. Data members are private; clients must go through the public getters, setters,
 * and calculatePriceInDollars(). Hiding the data lets the representation change later
 * without breaking callers.
 *
 * Key notes:
 *   - The "m_" prefix on data members is convention - not enforced by the language but
 *     useful to distinguish members from locals at a glance.
 *   - In-class initializers ("int m_n { 0 };") give each member a default. With every
 *     member already initialized, a hand-written default constructor is unnecessary, which
 *     is why the commented-out constructor/destructor stay commented out.
 *   - "struct" and "class" only differ in default access (public vs private).
 *   - "#pragma once" is the modern alternative to #ifndef/#define include guards and is
 *     supported by all major compilers.
 *   - Member functions defined elsewhere are introduced with "ClassName::method".
 */

#include <string>

class AirlineTicket
{
public:
	//AirlineTicket();
	//~AirlineTicket();

	double calculatePriceInDollars();
	
	std::string getPassengerName();
	void setPassengerName(std::string name);

	int getNumberOfMiles();
	void setNumberOfMiles(int miles);
	
	bool hasEliteSuperRewardsStatus();
	void setHasEliteSuperRewardsStatus(bool status);

private:
	//std::string m_passengerName;
	//int m_numberOfMiles;
	//bool m_hasEliteSuperRewardsStatus;
	std::string m_passengerName{ "Unknown Passenger" };
	int m_numberOfMiles{ 0 };
	bool m_hasEliteSuperRewardsStatus{ false };
};
