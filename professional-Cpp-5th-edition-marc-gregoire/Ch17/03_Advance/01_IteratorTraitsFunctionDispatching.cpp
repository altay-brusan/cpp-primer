/*
 * Chapter 17 - Tag Dispatching on Iterator Category
 *
 * Reimplements std::advance() the classic way: tag dispatching. myAdvance() reads
 * iterator_traits<Iter>::iterator_category and passes a default-constructed tag
 * object (input_iterator_tag, bidirectional_iterator_tag, or
 * random_access_iterator_tag) to overloaded advanceHelper() functions. The compiler
 * selects the most efficient implementation per category: stepping ++ for input,
 * +/- for bidirectional, and a single += for random access. Tested against a vector
 * (random-access) and a list (bidirectional) so different overloads are chosen.
 *
 * Key notes:
 *   - This is the pre-C++20 technique; 02_UsingConcepts.cpp shows the modern
 *     concept-constrained equivalent.
 */

#include <print>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

template<typename Iter, typename Distance>
void advanceHelper(Iter& iter, Distance n, input_iterator_tag)
{
	while (n > 0) { ++iter; --n; }
}

template<typename Iter, typename Distance>
void advanceHelper(Iter& iter, Distance n, bidirectional_iterator_tag)
{
	while (n > 0) { ++iter; --n; }
	while (n < 0) { --iter; ++n; }
}

template<typename Iter, typename Distance>
void advanceHelper(Iter& iter, Distance n, random_access_iterator_tag)
{
	iter += n;
}

template<typename Iter, typename Distance>
void myAdvance(Iter& iter, Distance n)
{
	using category = typename iterator_traits<Iter>::iterator_category;
	advanceHelper(iter, n, category{});
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
