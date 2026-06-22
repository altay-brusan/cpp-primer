/*
 * Chapter 10 - Why Destructors Should Be Virtual (the broken version)
 *
 * This sample deliberately leaks. Base's destructor is not virtual, so
 * `delete ptr` where ptr is a `Base*` pointing at a `Derived` runs only
 * `~Base()`. `~Derived()` is never called, and `m_string` is never freed.
 *
 * Key notes:
 *   - Any class that may be used polymorphically (anyone might delete it via
 *     a base pointer) MUST have a virtual destructor. If you write `virtual`
 *     anywhere else in the class, you almost certainly need it here too.
 *   - The companion file 02_VirtualDestructors.cpp shows the one-line fix.
 *   - In modern code, prefer `std::unique_ptr<char[]>` or `std::string` over a
 *     raw `new char[30]`. The raw pointer is kept here to make the leak
 *     visible in the trace output.
 */
#include <print>

using namespace std;

class Base
{
public:
	Base() = default;
	~Base() {}                  // NOT virtual - bug
};

class Derived : public Base
{
public:
	Derived()
	{
		m_string = new char[30];
		println("m_string allocated");
	}

	~Derived()
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
	delete ptr;                   // ~Base only - ~Derived skipped, m_string leaks.
}
