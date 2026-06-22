/*
 * Chapter 10 - Hiding Instead of Overriding
 *
 * If a base class function is NOT virtual and the derived class declares a
 * function with the same name, the derived version *hides* the base version
 * rather than overriding it. Which one runs is decided at compile time from
 * the static type of the expression - the dynamic type does not matter.
 *
 * Key notes:
 *   - Static dispatch: `myDerived.someFunction()` resolves to Derived's because
 *     the compiler knows the static type is Derived.
 *   - But `Base& ref{ myDerived }; ref.someFunction();` calls Base's version,
 *     because there's no vtable to dispatch through. This silently does the
 *     wrong thing if you expected polymorphism.
 *   - Rule of thumb: make any function intended to be overridden `virtual`.
 *     Mark the override with `override` so the compiler shouts if the
 *     signature ever drifts away from the base.
 */
#include <print>

using namespace std;

class Base
{
public:
	void someFunction()   // NOT virtual - this is the bug seed
	{
		println("Base::someFunction()");
	}

protected:
	int m_protectedInt{ 0 };

private:
	int m_privateInt{ 0 };
};

class Derived : public Base
{
public:
	void someFunction()   // hides Base::someFunction(), does not override it
	{
		println("Derived::someFunction()");
	}

	void someOtherFunction()
	{
		println("I can access base class data member m_protectedInt.");
		println("Its value is {}", m_protectedInt);
		//println("The value of m_privateInt is {}", m_privateInt); // Error!
	}
};

int main()
{
	{
		Derived myDerived;
		myDerived.someFunction();   // Derived's - static type is Derived.
	}

	{
		Derived myDerived;
		Base& ref{ myDerived };
		ref.someFunction();         // Base's - static dispatch on Base&, not virtual.
	}
}
