#pragma once

/*
 * Chapter 1 - Defining Classes
 *
 * A class definition declares the data members and methods of a new type. Each member has an
 * access level (public, protected, or private). Make data members private and expose them
 * through public getters and setters; the representation can then change later without
 * breaking client code. The "m_" prefix on data members is a convention - not enforced by
 * the language, but useful to distinguish members from locals at a glance.
 *
 * Key notes:
 *   - A method with the same name as the class and no return type is a constructor; one
 *     prefixed with "~" is a destructor.
 *   - In-class initializers ("int m_n { 0 };") set the default value next to the declaration.
 *     If every member has one and nothing else needs to run, you can skip the constructor
 *     entirely - which is why the constructor/destructor pair below is commented out.
 *   - Member functions can be defined inline in the class body or out of line with the
 *     ClassName::method syntax in a separate .cpp.
 *   - Constructor initializer list: "ClassName() : m_a { 1 }, m_b { 2 } { /* body */ }".
 *     Members are initialized in declaration order, not list order.
 *   - "struct" and "class" only differ in default access (public vs private).
 *   - Add an explicit destructor only when you have cleanup to do (closing files, freeing
 *     memory). For owned resources, prefer RAII types like std::unique_ptr / std::vector.
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
