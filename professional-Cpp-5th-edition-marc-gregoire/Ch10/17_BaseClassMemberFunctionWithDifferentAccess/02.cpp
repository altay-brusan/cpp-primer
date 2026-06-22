/*
 * Chapter 10 - Changing Access (2/4): Calling a protected base function from derived
 *
 * `Secret::dontTell()` is protected, so external code can't call it. But
 * `Blabber::tell()` (which IS public) can call it because Blabber is in
 * Secret's "friends-and-derived" group.
 *
 * Key notes:
 *   - "protected" is "accessible from this class and its derivatives", not
 *     "accessible from related classes".
 *   - This is how derived classes safely expose curated views of base
 *     behavior - publish a new public function whose body calls the protected
 *     one.
 */
#include <print>

using namespace std;

class Secret
{
protected:
	virtual void dontTell() { println("I'll never tell."); }
};

class Blabber : public Secret
{
public:
	virtual void tell() { dontTell(); }    // legal - protected member of base, called from derived
};

int main()
{
	Blabber myBlabber;
	myBlabber.tell();   // Outputs "I'll never tell."
}
