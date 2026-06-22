/*
 * Chapter 10 - Constructor and Destructor Chaining
 *
 * The order in which constructors and destructors run when inheritance and
 * data members are combined. C++ guarantees:
 *
 *   1. Base constructors run before Derived.
 *   2. Within a class, data members are constructed in declaration order
 *      (not in the order they appear in the ctor-initializer list).
 *   3. Destructors run in the exact reverse order.
 *
 * Trace this program by reading the numbers it prints:
 *   - Stack-allocated case prints `123321`: Base(1), Something member(2),
 *     Derived(3); then ~Derived(3), ~Something(2), ~Base(1).
 *   - Heap case with virtual destructor produces the same sequence because
 *     `delete ptr` correctly calls ~Derived first.
 *
 * Key notes:
 *   - If ~Base() were not virtual, the heap case would only print `12331`
 *     (no ~Something, no ~Derived). The leak section of the chapter exists
 *     precisely because of this.
 *   - The Something member is constructed AFTER Base but BEFORE Derived's
 *     body, because data-member initialization happens during the implicit
 *     part of the Derived constructor.
 */
#include <print>

using namespace std;

class Something
{
public:
	Something() { print("2"); }
	virtual ~Something() { print("2"); }
};

class Base
{
public:
	Base() { print("1"); }
	virtual ~Base() { print("1"); }
};

class Derived : public Base
{
public:
	Derived() { print("3"); }
	virtual ~Derived() override { print("3"); }

private:
	Something m_dataMember;   // constructed after Base, destroyed before Base
};


int main()
{
	{
		Derived myDerived;     // prints 1 2 3 ... then on scope exit: 3 2 1
	}

	println("");

	{
		Base* ptr{ new Derived{} };
		delete ptr;            // virtual ~Base means ~Derived runs first - same 123 / 321 trace
	}
}
