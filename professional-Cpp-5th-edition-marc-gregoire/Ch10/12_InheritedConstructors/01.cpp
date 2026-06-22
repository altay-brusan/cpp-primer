/*
 * Chapter 10 - Inherited Constructors (1/5): The Problem
 *
 * If Base has a useful constructor (here `Base(int)`), Derived does NOT
 * automatically get it. Derived has to either define its own forwarding ctor
 * or use a `using` declaration (see 02.cpp).
 *
 * Also note: declaring any non-default ctor on Derived suppresses its implicit
 * default ctor, so `Derived d;` no longer compiles.
 *
 * Key notes:
 *   - Constructors are NOT inherited by default. They're per-class.
 *   - `explicit` on a single-argument ctor blocks implicit conversion - so
 *     `Base b = 1;` won't compile, but `Base b{1};` will.
 *   - 02.cpp shows the fix with `using Base::Base;`.
 */
class Base
{
public:
	virtual ~Base() = default;
	Base() = default;
	explicit Base(int i) {}
};

class Derived : public Base
{
public:
	Derived(int i) : Base(i) {}   // manual forwarding ctor
};

int main()
{
	Base base{ 1 };          // OK, calls integer Base ctor.
	Derived derived1{ 2 };   // OK, calls integer Derived ctor.
	//Derived derived2;      // Error, Derived does not have a default ctor.
}
