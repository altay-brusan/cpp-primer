/*
 * Chapter 10 - Inherited Constructors (5/5): Derived members get default-initialized
 *
 * When you inherit a base constructor via `using Base::Base;`, the Derived
 * class's own data members are NOT mentioned in that inherited ctor. They are
 * default-initialized (using in-class initializers if present).
 *
 * Here `Derived` adds `m_int` with an in-class initializer of `0`. When the
 * compiler synthesizes the inherited `Derived(string_view)` from Base's ctor,
 * it leaves `m_int` at its in-class default of 0. That's usually fine.
 *
 *   - `Derived s1{2};`          -> uses local Derived(int): Base{""} + m_int{2}
 *   - `Derived s2{"Hello..."};` -> uses inherited Base(string_view): m_int{0}
 *
 * Key notes:
 *   - Always use in-class initializers for Derived data members when you plan
 *     to inherit constructors - otherwise the inherited ctor leaves them
 *     uninitialized (for fundamental types) or in their default state.
 *   - The local `Derived(int)` here illustrates mixing: an inherited Base ctor
 *     for the string case, plus a hand-written Derived ctor for the int case.
 */
#include <string_view>
#include <string>

class Base
{
public:
	virtual ~Base() = default;
	explicit Base(std::string_view str) : m_str{ str } {}
private:
	std::string m_str;
};

class Derived : public Base
{
public:
	using Base::Base;
	explicit Derived(int i) : Base{ "" }, m_int{ i } {}
private:
	int m_int{ 0 };      // in-class default keeps inherited ctors safe
};


int main()
{
	Derived s1{ 2 };
	Derived s2{ "Hello World" };
}
