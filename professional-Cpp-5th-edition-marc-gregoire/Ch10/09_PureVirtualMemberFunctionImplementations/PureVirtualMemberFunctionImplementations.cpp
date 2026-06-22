/*
 * Chapter 10 - Implementing a Pure Virtual Member Function
 *
 * Surprising rule: a function declared `= 0` (pure virtual) *can* still have a
 * definition. The `= 0` makes the class abstract; the definition gives derived
 * classes a fallback they can opt into with a qualified call.
 *
 * Key notes:
 *   - The line `virtual void doSomething() = 0;` says "Base is abstract; no one
 *     can instantiate it directly".
 *   - The line `void Base::doSomething() { ... }` provides the body. Pure does
 *     not mean "no body" - it means "not enough on its own".
 *   - Derived calls `Base::doSomething();` explicitly to chain the fallback,
 *     just like the Book/Paperback/Romance sample. The qualified call also
 *     bypasses virtual dispatch (otherwise it would loop forever).
 *   - Common use case: shared cleanup logic that every concrete subclass needs
 *     but can't rely on the default implementation alone.
 */
#include <print>

using namespace std;

class Base
{
public:
	virtual ~Base() = default;
	virtual void doSomething() = 0; // Pure virtual member function.
};

// Definition of the pure virtual function lives outside the class.
void Base::doSomething() { println("Base::doSomething()"); }

class Derived : public Base
{
public:
	void doSomething() override
	{
		// Call the pure-virtual fallback from the base class.
		Base::doSomething();
		println("Derived::doSomething()");
	}
};

int main()
{
	Derived derived;
	Base& base{ derived };
	base.doSomething();   // virtual dispatch -> Derived::doSomething -> chains to Base::doSomething
}
