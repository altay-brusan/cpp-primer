/*
 * Chapter 26 - Printing a Tuple with Template Recursion
 *
 * A tuple has a fixed compile-time size but no built-in iteration, so this
 * sample iterates its elements using template recursion. TuplePrint<TupleType,
 * N> constructs TuplePrint<TupleType, N-1> in its constructor and then prints
 * get<N-1>(t); the partial specialization TuplePrint<TupleType, 0> ends the
 * recursion.
 *
 * Key notes:
 *   - The instantiation in main() must spell out the tuple type and its size via
 *     tuple_size, which the later samples simplify.
 */

#include <print>
#include <tuple>
#include <string>

using namespace std;

template <typename TupleType, int N>
class TuplePrint
{
public:
	explicit TuplePrint(const TupleType& t) {
		TuplePrint<TupleType, N - 1> tp{ t };
		println("{}", get<N - 1>(t));
	}
};

template <typename TupleType>
class TuplePrint<TupleType, 0>
{
public:
	explicit TuplePrint(const TupleType&) { }
};

int main()
{
	using MyTuple = tuple<int, string, bool>;
	MyTuple t1{ 16, "Test", true };
	TuplePrint<MyTuple, tuple_size<MyTuple>::value> tp{ t1 };
}
