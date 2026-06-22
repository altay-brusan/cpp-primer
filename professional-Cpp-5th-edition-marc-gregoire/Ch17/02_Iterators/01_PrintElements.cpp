/*
 * Chapter 17 - Iterating Over a Container with Iterators
 *
 * Shows the basic iterator idiom: looping from cbegin(values) to cend(values) and
 * dereferencing with operator* to print each element. The canonical end-of-range
 * test uses != rather than <, because != works on all iterator categories while <
 * is only available on random-access iterators. The myPrint() helper generalizes
 * the loop to any [begin, end) range and is constrained with the input_iterator
 * concept.
 */

#include <print>
#include <vector>
#include <iterator>

using namespace std;

template<input_iterator Iter>
void myPrint(Iter begin, Iter end)
{
	for (auto iter{ begin }; iter != end; ++iter) {
		print("{} ", *iter);
	}
}

int main()
{
	vector values{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	for (auto iter{ cbegin(values) }; iter != cend(values); ++iter) {
		print("{} ", *iter);
	}
	println("");

	myPrint(cbegin(values), cend(values));
	println("");
}