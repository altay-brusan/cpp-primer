/*
 * Chapter 10 - Copy Constructor and Assignment in a Derived Class
 *
 * If you write a copy constructor or copy assignment in a derived class, you
 * MUST call the base versions yourself. The compiler will not chain them for
 * you - it only chains for *implicit* (defaulted/synthesized) special members.
 *
 *   - Copy ctor: `Derived(const Derived& src) : Base{src} { ... }`
 *     Initialize the Base sub-object from `src` in the ctor-initializer.
 *   - operator=:  call `Base::operator=(rhs)` explicitly in the body.
 *
 * The self-assignment check (`&rhs == this`) is shown for clarity. Modern
 * code usually skips it and reaches for the copy-and-swap idiom from Ch09
 * which is self-assignment safe by construction.
 */
class Base
{
public:
	virtual ~Base() = default;
	Base() = default;
	Base(const Base& src) { }
	Base& operator=(const Base& rhs) = default;
};

class Derived : public Base
{
public:
	Derived() = default;

	Derived(const Derived& src) : Base{ src } { }   // chain Base's copy ctor

	Derived& operator=(const Derived& rhs)
	{
		if (&rhs == this) {
			return *this;
		}
		Base::operator=(rhs);   // chain Base's assignment
		// ... Derived-specific copies would go here ...
		return *this;
	}
};

int main()
{
	Derived d1;
	Derived d2{ d1 };
	d2 = d1;
}
