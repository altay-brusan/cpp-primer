/*
 * Chapter 26 - constexpr if with a requires Expression
 *
 * Instead of testing inheritance, callDoit() here uses
 * if constexpr (requires { t.doit(); }) to detect directly whether the
 * expression is valid for the given type. This duck-typing style checks for the
 * capability itself rather than for a specific base class.
 */

#include <print>
#include <type_traits>

using namespace std;

class IsDoable
{
public:
	void doit() const { println("IsDoable::doit()"); }
};

class Derived : public IsDoable
{
};

template<typename T>
void callDoit(const T& t)
{
	if constexpr (requires { t.doit(); }) {
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
