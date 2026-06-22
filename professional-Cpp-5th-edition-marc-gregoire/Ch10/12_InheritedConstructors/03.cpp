/*
 * Chapter 10 - Inherited Constructors (3/5): Derived ctors hide inherited ones
 *
 * `using Base::Base;` brings Base's ctors into Derived, but a Derived ctor
 * with the same signature as an inherited one HIDES the inherited version.
 * Here `Derived(float)` is defined locally, so the inherited `Base(float)` is
 * unreachable through Derived.
 *
 *   - `Derived d1{"Hello"}` -> uses inherited Base(string_view)
 *   - `Derived d2{1.23f}`   -> uses local Derived(float), NOT inherited Base(float)
 *   - `Derived d3`          -> uses inherited Base()
 *
 * Key notes:
 *   - Hiding is by full signature: matching parameter types + cv-qualifiers.
 *   - This is usually what you want: your derived class adds its own logic for
 *     the case it cares about, while letting the rest pass through.
 */
#include <string_view>

class Base
{
public:
	virtual ~Base() = default;
	Base() = default;
	explicit Base(std::string_view str) {}
	explicit Base(float f) {}
};

class Derived : public Base
{
public:
	using Base::Base;
	explicit Derived(float f) {}    // hides the inherited Base(float) ctor
};


int main()
{
	Derived derived1{ "Hello" };   // inherited string_view Base ctor
	Derived derived2{ 1.23f };     // local Derived(float)
	Derived derived3;              // inherited default Base ctor
}
