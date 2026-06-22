/*
 * Chapter 24 - Implementing operator<=> via std::tie
 *
 * Demonstrates using tuple comparison together with the C++20 three-way
 * comparison operator (operator<=>) to give a class lexicographical comparison
 * operators in a single line. tie() builds tuples of references to the data
 * members of both operands and compares them with <=>; the compiler then derives
 * <, >, <=, and >= from that result. This version intentionally compares only a
 * subset of the members (m_int and m_str, omitting m_bool) to show that tie()
 * lets you choose which members participate, rather than using a defaulted
 * operator<=> that would compare them all.
 */

#include <print>
#include <compare>
#include <string>
#include <tuple>
#include <utility>

using namespace std;

class Foo
{
public:
	explicit Foo(int i, string s, bool b)
		: m_int{ i }, m_str{ move(s) }, m_bool{ b }
	{
	}

	// Explicitly default operator<=>
	//auto operator<=>(const Foo& rhs) const = default;
	
	// Compare a subset of the data members.
	auto operator<=>(const Foo& rhs) const
	{
		return tie(m_int, m_str) <=> tie(rhs.m_int, rhs.m_str);
	}
private:
	int m_int;
	string m_str;
	bool m_bool;
};

int main()
{
	Foo f1{ 42, "Hello", false };
	Foo f2{ 42, "World", false };
	println("{}", (f1 < f2));  // Outputs true
	println("{}", (f2 > f1));  // Outputs true
}
