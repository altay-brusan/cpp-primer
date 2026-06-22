/*
 * Chapter 10 - Default Arguments and Virtual Functions Don't Mix Well
 *
 * Surprising rule: default arguments are bound by the *static* type, but the
 * function body is dispatched by the *dynamic* type. The result is a
 * Frankenstein call: Derived's body runs but with Base's default value.
 *
 * Trace the output:
 *   - myBase.go()                       -> Base's body, i=2  (Base's default)
 *   - myDerived.go()                    -> Derived's body, i=7 (Derived's default)
 *   - myBaseReferenceToDerived.go()     -> Derived's body, i=2 (Base's default!)
 *
 * Key notes:
 *   - This is almost always a bug. Pick one and only one place to put the
 *     default - usually the base, never the override - or just don't use
 *     defaults on virtual functions.
 *   - Putting different defaults on Base and Derived is the worst combination
 *     because behavior changes silently based on the static type of the
 *     reference you happen to be calling through.
 */
#include <print>

using namespace std;

class Base
{
public:
	virtual ~Base() = default;
	virtual void go(int i = 2) { println("Base's go with i={}", i); }
};

class Derived : public Base
{
public:
	void go(int i = 7) override { println("Derived's go with i={}", i); }
};

int main()
{
	Base myBase;
	Derived myDerived;
	Base& myBaseReferenceToDerived{ myDerived };
	myBase.go();                      // Base body, i=2
	myDerived.go();                   // Derived body, i=7
	myBaseReferenceToDerived.go();    // Derived body, i=2  - the bug
}
