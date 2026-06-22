/*
 * Chapter 10 - Static Member Functions Don't Polymorph
 *
 * `static` member functions belong to the *class*, not to an object. They
 * have no `this`, no vtable entry, and no notion of dynamic dispatch. A
 * derived class can declare a same-named static function, but that just hides
 * the base one - it does NOT override anything.
 *
 * Key notes:
 *   - `BaseStatic::beStatic()` and `DerivedStatic::beStatic()` are two unrelated
 *     functions that happen to share a name.
 *   - Calling `beStatic()` through a `BaseStatic&` always picks the Base one,
 *     even when the reference binds to a DerivedStatic - because static
 *     functions are dispatched on the static type, period.
 *   - Don't try to "override" a static function. If you need polymorphism, the
 *     base function can't be static.
 */
#include <print>

using namespace std;

class BaseStatic
{
public:
	static void beStatic() {
		println("BaseStatic being static.");
	}
};

class DerivedStatic : public BaseStatic
{
public:
	static void beStatic() {
		println("DerivedStatic keepin' it static.");
	}
};

int main()
{
	{
		BaseStatic::beStatic();
		DerivedStatic::beStatic();
	}

	{
		DerivedStatic myDerivedStatic;
		BaseStatic& ref{ myDerivedStatic };
		myDerivedStatic.beStatic();   // DerivedStatic - static type wins.
		ref.beStatic();               // BaseStatic    - static type wins; no virtual dispatch.
	}
}
