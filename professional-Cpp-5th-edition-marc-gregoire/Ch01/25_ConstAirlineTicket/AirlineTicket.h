#pragma once

/*
 * Chapter 1 - const Methods
 *
 * A "const" after a member function's parameter list (e.g. "std::string getName() const;")
 * declares that the function does not modify the object's observable state. The compiler
 * enforces it: any assignment to a data member, or call to a non-const method, from inside
 * a const method is rejected.
 *
 * Key notes:
 *   - Methods that only read state are called inspectors and should be const. Methods that
 *     change state are mutators and stay non-const.
 *   - Only const methods can be called on a const object or through a reference-to-const /
 *     pointer-to-const. Forgetting to mark a getter const limits callers unnecessarily.
 *   - Const-correctness is viral: marking parameters const often forces the methods called
 *     on them to be const too. Apply it from the leaf upward.
 *   - "mutable" lets a specific data member be modified even inside a const method. Use it
 *     sparingly - typical legitimate use is a cache or a mutex.
 *   - Logical vs bitwise constness: bitwise = no bit of the object changes; logical = no
 *     observable behavior changes. const enforces bitwise; mutable lets you preserve logical
 *     constness while updating internal helpers like a cache.
 *   - The "const" applies to the implicit "this" pointer - inside the method, this has type
 *     "const T*".
 */

#include <string>

class AirlineTicket
{
public:
	double calculatePriceInDollars() const;
	
	std::string getPassengerName() const;
	void setPassengerName(std::string name);

	int getNumberOfMiles() const;
	void setNumberOfMiles(int miles);
	
	bool hasEliteSuperRewardsStatus() const;
	void setHasEliteSuperRewardsStatus(bool status);

private:
	std::string m_passengerName{ "Unknown Passenger" };
	int m_numberOfMiles{ 0 };
	bool m_hasEliteSuperRewardsStatus{ false };
};
