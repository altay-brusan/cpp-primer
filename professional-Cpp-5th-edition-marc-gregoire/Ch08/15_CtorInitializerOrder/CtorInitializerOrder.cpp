/*
 * Chapter 8 - Initialization Order in a ctor-initializer
 *
 * The visual order of entries in a ctor-initializer list is misleading. C++ initializes
 * data members in the order they appear in the class definition, regardless of how you
 * write them in the list. In this program, `m_foo` is declared before `m_value`, so the
 * Foo constructor runs first - and it runs with `m_value` still uninitialized. Reversing
 * the declared order of the two members would fix this; reordering the ctor-initializer
 * list alone would not.
 *
 * Key notes:
 *   - Members are initialized in declaration order; the ctor-initializer list is just a
 *     list of arguments, not an execution order.
 *   - Reading another member during initialization is safe only if the other member is
 *     declared (and therefore initialized) first.
 *   - Some compilers warn when the list order does not match declaration order - enable
 *     those warnings.
 *   - The safe fix here is `m_foo { value }` - depend on the constructor parameter, not on
 *     the half-initialized `m_value`.
 */

#include <print>

using namespace std;

class Foo
{
public:
	Foo(double value);

private:
	double m_value{ 0 };
};

Foo::Foo(double value) : m_value{ value }
{
	println("Foo::m_value = {}", m_value);
}

class MyClass
{
public:
	MyClass(double value);

private:
	Foo m_foo;
	double m_value{ 0 };
};

MyClass::MyClass(double value)
	: m_value{ value }   // written first in the list...
	, m_foo{ m_value }   // ...but m_foo is declared first, so this line runs FIRST with garbage m_value
{
	println("MyClass::m_value = {}", m_value);
}

int main()
{
	MyClass instance{ 1.2 };
}