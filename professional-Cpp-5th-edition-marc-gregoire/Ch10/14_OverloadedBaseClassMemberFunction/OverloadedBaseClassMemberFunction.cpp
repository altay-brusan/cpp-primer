/*
 * Chapter 10 - Overriding One Overload Hides the Others
 *
 * Surprise rule: if Derived overrides `overload()` but Base has both
 * `overload()` and `overload(int)`, the int version becomes inaccessible
 * through a Derived object. The act of declaring `overload` in Derived hides
 * EVERY same-named function from the base.
 *
 * Two workarounds:
 *   - `using Base::overload;` - pulls all the base overloads back into scope.
 *     (Commented out in the code; uncomment to make `myDerived.overload(2)` work.)
 *   - Call through a `Base&`. Virtual dispatch still goes to Derived for the
 *     no-arg version, but `ref.overload(7)` finds Base::overload(int) because
 *     name lookup happens on the base interface.
 *
 * Key notes:
 *   - This is one of the most common silent bugs in inheritance. `override`
 *     does NOT save you from it.
 *   - Default rule: when you override one overload, add a `using Base::name;`
 *     to keep the rest reachable.
 */
#include <print>

using namespace std;

class Base
{
public:
	virtual ~Base() = default;
	virtual void overload() { println("Base's overload()"); }
	virtual void overload(int i) { println("Base's overload(int i)"); }
};

class Derived : public Base
{
public:
	//using Base::overload;   // <-- uncomment to expose the int overload again
	void overload() override { println("Derived's overload()"); }
};

int main()
{
	{
		Derived myDerived;
		//myDerived.overload(2); // Error! No matching member function for overload(int).
	}

	{
		Derived myDerived;
		Base& ref{ myDerived };
		ref.overload(7);          // Base::overload(int) reached via Base& - name lookup on Base.
	}
}
