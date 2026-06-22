/*
 * Chapter 10 - Inheritance Basics
 *
 * The simplest possible inheritance example. `Derived : public Base` means every
 * Derived "is-a" Base: it gets Base's public and protected members, plus the
 * vtable, plus an implicit Base sub-object that the Derived constructor sets up
 * before its own body runs.
 *
 * Key notes:
 *   - `public` inheritance is the default modeling choice ("is-a"). `protected`
 *     and `private` inheritance exist but model "implemented-in-terms-of" and
 *     are rare in practice.
 *   - Derived can touch Base's `protected` members; it CANNOT touch Base's
 *     `private` ones. Access is granted to the derived class, not bypassed.
 *   - A `Base*` can point at a `Derived` (upcasting is implicit and safe), but
 *     calling Derived-only members through that pointer is a compile error -
 *     the static type drives name lookup, not the dynamic one.
 *   - This sample uses no `virtual` yet, so dispatch is purely static. Virtual
 *     dispatch shows up in the next sample.
 */
#include <print>

using namespace std;

class Base
{
public:
	void someFunction() {}

protected:
	int m_protectedInt{ 0 };   // derived classes can read/write this

private:
	int m_privateInt{ 0 };     // off-limits to derived classes
};

class Derived : public Base
{
public:
	void someOtherFunction()
	{
		println("I can access base class data member m_protectedInt.");
		println("Its value is {}", m_protectedInt);
		//println("The value of m_privateInt is {}", m_privateInt); // Error!
	}
};

int main()
{
	Derived myDerived;
	myDerived.someFunction();       // inherited from Base
	myDerived.someOtherFunction();  // declared in Derived

	Base myBase;
	//myBase.someOtherFunction();   // Error! Base doesn't have a someOtherFunction().

	Base* base{ new Derived{} };    // upcast - allowed implicitly.

	//base->someOtherFunction();    // Error! Static type Base lacks someOtherFunction().

	delete base;                    // leak fix - and a setup for the virtual-destructor sample
}
