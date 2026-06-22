/*
 * Chapter 26 - Simplifying enable_if with constexpr if
 *
 * The same callDoit() collapsed into one function template using
 * if constexpr (is_base_of_v<IsDoable, T>). The t.doit() call lives in a branch
 * that is not compiled for unrelated types, which a normal if cannot achieve
 * because both branches of a normal if must always compile.
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
void callDoit(const T& t)
{
	if constexpr (is_base_of_v<IsDoable, T>) {
		t.doit();
	} else {
		println("Cannot call doit()!");
	}
}

int main()
{
	Derived d;
	callDoit(d);
	callDoit(123);
}
