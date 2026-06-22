/*
 * Chapter 24 - std::make_from_tuple
 *
 * Demonstrates std::make_from_tuple<T>(), which constructs an object of type T by
 * unpacking the elements of a tuple and forwarding them as constructor arguments.
 * Here a tuple of (const char-pointer, int) is used to build a Foo whose
 * constructor takes (string, int). The argument need not be a literal tuple - any
 * type supporting get<>() and tuple_size (such as array or pair) works. This is
 * mainly useful in generic and template-metaprogramming code rather than everyday
 * use. Note: this sample has no console output.
 */

#include <tuple>
#include <string>
#include <utility>

using namespace std;

class Foo
{
public:
	explicit Foo(string str, int i) : m_str{ move(str) }, m_int{ i } {}

private:
	string m_str;
	int m_int;
};

int main()
{
	tuple myTuple{ "Hello world.", 42 };
	auto foo{ make_from_tuple<Foo>(myTuple) };
}
