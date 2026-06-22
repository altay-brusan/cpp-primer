/*
 * Chapter 10 - Overriding Virtual Member Functions
 *
 * Once a base class function is `virtual`, the call site dispatches through the
 * vtable, so the *dynamic* type of the object selects the implementation. Same
 * code, very different runtime behavior than the hiding sample.
 *
 * Key notes:
 *   - `virtual` on Base + `override` on Derived: now `Base& ref{ derived };
 *     ref.someFunction();` correctly runs Derived's version.
 *   - `override` is not strictly required, but it makes the compiler verify
 *     that you are really overriding something. A typo or const mismatch turns
 *     a silent bug into a build error.
 *   - Slicing: `Base assignedObject{ myDerived };` constructs a *Base*. The
 *     Derived parts (data and the dynamic type) are sliced off. Calls on the
 *     copy are forever Base calls. Slicing happens when you copy by value
 *     across the inheritance boundary - prefer references or pointers for
 *     polymorphic use.
 *   - Calling a Derived-only member through a Base& is still a compile error.
 *     Virtual dispatch lets Derived *replace* a Base function, not add to the
 *     Base interface.
 */
#include <print>

using namespace std;

class Base
{
public:
	virtual void someFunction();   // virtual - dispatched at runtime

protected:
	int m_protectedInt{ 0 };

private:
	int m_privateInt{ 0 };
};

void Base::someFunction()
{
	println("This is Base's version of someFunction().");
}



class Derived : public Base
{
public:
	void someFunction() override;  // overrides Base's someFunction()

	virtual void someOtherFunction()
	{
		println("I can access base class data member m_protectedInt.");
		println("Its value is {}", m_protectedInt);
		//println("The value of m_privateInt is {}", m_privateInt); // Error!
	}
};

void Derived::someFunction()
{
	println("This is Derived's version of someFunction().");
}



int main()
{
	{
		Base myBase;
		myBase.someFunction();           // Base's version.
	}

	{
		Derived myDerived;
		myDerived.someFunction();        // Derived's version.
	}

	{
		Derived myDerived;
		Base& ref{ myDerived };
		ref.someFunction();              // Derived's - virtual dispatch through the reference.
	}

	{
		Derived myDerived;
		Base& ref{ myDerived };
		myDerived.someOtherFunction();   // Allowed through Derived directly.
		// ref.someOtherFunction();      // Error - Base interface doesn't have it.
	}

	{
		Derived myDerived;
		Base assignedObject{ myDerived };  // *Slicing* - Derived parts are cut off.
		assignedObject.someFunction();     // Base's version - the object IS a Base now.
	}
}
