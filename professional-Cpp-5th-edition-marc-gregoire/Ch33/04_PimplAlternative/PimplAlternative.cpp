/*
 * Chapter 33 - Factory Method as a Pimpl Alternative
 *
 * Demonstrates using the Factory Method pattern to hide an implementation, an
 * alternative to the pimpl idiom from Chapter 9. The public Foo class exposes
 * only a pure-virtual interface plus a static create() factory function and a
 * protected constructor, so clients cannot instantiate it directly. The concrete
 * FooImpl subclass is defined privately and returned as a unique_ptr<Foo> from
 * create(), placing a clean wall between the public interface and the hidden
 * implementation.
 *
 * Key notes:
 *   - The protected constructor forces creation through the factory function.
 *   - Contains main(); run as a standalone program.
 */

#include <memory>

using namespace std;

// Public interface (to be included in the rest of the program,
// shared from a library, ...)
class Foo
{
public:
	virtual ~Foo() = default;  // Always a virtual destructor!
	Foo(const Foo&) = default;
	Foo& operator=(const Foo&) = default;
	Foo(Foo&&) = default;
	Foo& operator=(Foo&&) = default;

	static unique_ptr<Foo> create();  // Factory function.
	// Public functionality...
	virtual void bar() = 0;
protected:
	Foo() = default; // Protected default constructor.
};

// Implementation
class FooImpl : public Foo
{
public:
	void bar() override { /* ... */ }
};

unique_ptr<Foo> Foo::create()
{
	return make_unique<FooImpl>();
}

int main()
{
	auto fooInstance{ Foo::create() };
	fooInstance->bar();
}