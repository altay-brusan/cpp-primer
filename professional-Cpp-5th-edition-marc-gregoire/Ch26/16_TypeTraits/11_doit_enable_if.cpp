/*
 * Chapter 26 - Conditionally Calling a Method with enable_if
 *
 * callDoit() should call t.doit() only for types derived from IsDoable and
 * print an error otherwise. This version uses two enable_if_t overloads keyed on
 * is_base_of_v<IsDoable, T> to select the right behavior via SFINAE.
 */

#include <print>
#include <type_traits>

using namespace std;

class IsDoable
{
public:
	virtual void doit() const { println("IsDoable::doit()"); }
};

class Derived : public IsDoable
{
};

template<typename T>
enable_if_t<is_base_of_v<IsDoable, T>, void>
	callDoit(const T& t)
{
	t.doit();
}

template<typename T>
enable_if_t<!is_base_of_v<IsDoable, T>, void>
	callDoit(const T&)
{
	println("Cannot call doit()!");
}

int main()
{
	Derived d;
	callDoit(d);
	callDoit(123);
}
