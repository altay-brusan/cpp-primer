/*
 * Chapter 10 - Inherited Constructors (4/5): Multiple Inheritance Ambiguity
 *
 * Derived inherits ctors from both Base1 and Base2 via two `using` lines.
 * Both bases have `Base(float)`. If Derived didn't supply its own
 * `Derived(float)`, calling `Derived d{1.2f}` would be ambiguous - the
 * compiler couldn't tell which inherited Base(float) you meant.
 *
 * The fix shown here: define `Derived(float)` explicitly and have it
 * initialize *both* base sub-objects. That removes the ambiguity and lets
 * you decide how the value flows into each base.
 *
 *   - `Derived d{1.2f}` -> Derived(float) -> Base1(f) AND Base2(f)
 *   - `Derived d{'x'}`  -> Derived(char) (no Base ctor accepts char)
 */
#include <string_view>

class Base1
{
public:
	virtual ~Base1() = default;
	Base1() = default;
	explicit Base1(float f) {}
};

class Base2
{
public:
	virtual ~Base2() = default;
	Base2() = default;
	explicit Base2(std::string_view str) {}
	explicit Base2(float f) {}
};

class Derived : public Base1, public Base2
{
public:
	using Base1::Base1;
	using Base2::Base2;
	explicit Derived(char c) {}
	explicit Derived(float f) : Base1{ f }, Base2{ f } {}   // resolves the ambiguity
};


int main()
{
	Derived d{ 1.2f };
}
