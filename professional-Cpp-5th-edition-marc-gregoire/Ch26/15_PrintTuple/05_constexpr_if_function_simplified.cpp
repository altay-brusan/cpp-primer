/*
 * Chapter 26 - Tuple Printing in a Single Function Template
 *
 * Collapses the helper and wrapper into one recursive tuplePrint() by giving
 * its index parameter a default argument of tuple_size<TupleType>::value. The
 * constexpr if drives the recursion, so a single function template both starts
 * and performs the iteration.
 */

#include <print>
#include <tuple>
#include <string>

using namespace std;

template <typename TupleType, int N = tuple_size<TupleType>::value>
void tuplePrint(const TupleType& t)
{
	if constexpr (N > 1) {
		tuplePrint<TupleType, N - 1>(t);
	}
	println("{}", get<N - 1>(t));
}

int main()
{
	tuple t1{ 16, "Test"s, true };
	tuplePrint(t1);
}
