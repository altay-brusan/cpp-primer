/*
 * Chapter 26 - Tuple Printing with constexpr if (Class Version)
 *
 * Removes the base-case specialization by using a constexpr if (N > 1) inside
 * TuplePrintHelper's constructor to decide whether to recurse. Because the
 * untaken branch of a constexpr if is never compiled, the recursion terminates
 * cleanly without a separate stopping template.
 */

#include <print>
#include <tuple>
#include <string>

using namespace std;

template <typename TupleType, int N>
class TuplePrintHelper
{
public:
	explicit TuplePrintHelper(const TupleType& t) {
		if constexpr (N > 1) {
			TuplePrintHelper<TupleType, N - 1> tp{ t };
		}
		println("{}", get<N - 1>(t));
	}
};

template <typename T>
void tuplePrint(const T& t)
{
	TuplePrintHelper<T, tuple_size<T>::value> tph{ t };
}

int main()
{
	tuple t1{ 16, "Test"s, true };
	tuplePrint(t1);
}
