/*
 * Chapter 10 - Inherited Constructors (2/5): using Base::Base
 *
 * `using Base::Base;` brings ALL of Base's constructors into Derived. Now
 * `Derived d{2};` works (it forwards to `Base(int)`), and `Derived d;` works
 * too (it forwards to `Base()`).
 *
 * Key notes:
 *   - This is a single line that replaces a series of forwarding ctors.
 *   - It pulls in *only* the constructors. New Derived-specific data members
 *     would still default-initialize (or use their in-class initializers).
 *   - 03.cpp shows what happens when you mix `using Base::Base;` with a
 *     Derived ctor that has the same signature as an inherited one.
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
	using Base::Base;        // inherit all of Base's ctors
};

int main()
{
	Base base{ 1 };          // OK, calls integer Base ctor.
	Derived derived1{ 2 };   // OK, calls inherited integer Base ctor.
	Derived derived2;        // OK, calls inherited default Base ctor.
}
