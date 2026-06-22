/*
 * Chapter 10 - C++ Casts (4/4): dynamic_cast
 *
 * `dynamic_cast<T*>(p)` performs a *checked* downcast in a polymorphic
 * hierarchy. Two failure modes depending on what you cast TO:
 *   - Pointer form: returns `nullptr` on a bad cast.
 *   - Reference form: throws `std::bad_cast`.
 *
 * The example deliberately downcasts a Base reference that actually refers
 * to a Base to a Derived&. That can't succeed, so the throw branch runs.
 *
 * Key notes:
 *   - Requires a polymorphic base (at least one virtual function - the
 *     destructor counts) for typeid info to be available.
 *   - dynamic_cast has a runtime cost - it walks the class hierarchy. Avoid
 *     it on hot paths; prefer virtual functions when you can model the
 *     branching as method dispatch.
 *   - Use it for "downcasting at the edge" - e.g. a UI callback receives a
 *     base-class event, and you need to find out which concrete event you
 *     got.
 */
#include <print>
#include <typeinfo>

using namespace std;

class Base
{
public:
	virtual ~Base() = default;
};

class Derived : public Base
{
public:
	virtual ~Derived() = default;
};

int main()
{
	Base* b{ nullptr };
	Derived* d{ new Derived{} };

	b = d;
	d = dynamic_cast<Derived*>(b);   // succeeds: returns a non-null Derived*

	Base base;
	Derived derived;

	Base& br{ base };                // refers to an actual Base, NOT a Derived

	try {
		Derived& dr{ dynamic_cast<Derived&>(br) };   // throws bad_cast
	} catch (const bad_cast&) {
		println("Bad cast!");
	}

	delete d;   // cleanup; both b and d point at the same heap object
}
