/*
 * Chapter 10 - Why Destructors Should Be Virtual (the fixed version)
 *
 * Same setup as 01_VirtualDestructors.cpp, but now Base has a virtual
 * destructor. `delete ptr` on a `Base*` follows the vtable to `~Derived()`,
 * which runs first and frees `m_string`, then `~Base()` runs implicitly.
 *
 * Key notes:
 *   - `virtual ~Base() = default;` is the canonical declaration for a
 *     polymorphic base. `= default` gives you a compiler-generated body and
 *     keeps the destructor trivial when possible.
 *   - `~Derived() override` is recommended for the same reason `override`
 *     helps elsewhere - the compiler verifies you are really overriding.
 *   - Destructor calls chain bottom-up: derived destructors run first, then
 *     base. Constructors run the opposite direction (top-down).
 */
#include <print>

using namespace std;

class Base
{
public:
	Base() = default;
	virtual ~Base() = default;     // the fix
};

class Derived : public Base
{
public:
	Derived()
	{
		m_string = new char[30];
		println("m_string allocated");
	}

	~Derived() override
	{
		delete[] m_string;
		println("m_string deallocated");
	}

private:
	char* m_string;
};

int main()
{
	Base* ptr{ new Derived{} };   // m_string is allocated here.
	delete ptr;                   // ~Derived first, then ~Base - no leak.
}
