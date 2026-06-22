/*
 * Chapter 17 - Selecting Iterator Behavior with Concepts
 *
 * The C++20 counterpart to tag dispatching. Three overloads of myAdvance() are
 * constrained directly with the standard iterator concepts input_iterator,
 * bidirectional_iterator, and random_access_iterator. Because the concepts form a
 * refinement hierarchy, the compiler picks the most specialized (most constrained)
 * overload that the iterator satisfies, giving the same per-category dispatch as
 * iterator_traits tags but with clearer, more direct code. Tested with a vector and
 * a list.
 */

#include <print>
#include <vector>
#include <list>
#include <iterator>
#include <concepts>

using namespace std;

template<input_iterator Iter, typename Distance>
void myAdvance(Iter& iter, Distance n)
{
	while (n > 0) { ++iter; --n; }
}

template<bidirectional_iterator Iter, typename Distance>
void myAdvance(Iter& iter, Distance n)
{
	while (n > 0) { ++iter; --n; }
	while (n < 0) { --iter; ++n; }
}

template<random_access_iterator Iter, typename Distance>
void myAdvance(Iter& iter, Distance n)
{
	iter += n;
}

template<typename Iter>
void testAdvance(Iter iter)
{
	print("*iter = {} | ", *iter);
	myAdvance(iter, 3); print("3 ahead = {} | ", *iter);
	myAdvance(iter, -2); println("2 back = {}", *iter);
}

int main()
{
	vector vec{ 1, 2, 3, 4, 5, 6 };
	testAdvance(begin(vec));

	list lst{ 1, 2, 3, 4, 5, 6 };
	testAdvance(begin(lst));
}
