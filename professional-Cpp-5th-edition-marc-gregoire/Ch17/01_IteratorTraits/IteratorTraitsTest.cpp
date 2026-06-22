/*
 * Chapter 17 - Iterator Traits
 *
 * Demonstrates the std::iterator_traits class template from <iterator>. The
 * iteratorTraitsTest() function template instantiates iterator_traits with the
 * iterator type passed in and uses the value_type alias to declare a temporary of
 * the same type the iterator refers to. Calling it with cbegin(v) on a vector<int>
 * makes value_type resolve to int. Note the typename keyword required when accessing
 * a type that depends on a template type parameter.
 *
 * Key notes:
 *   - iterator_traits exposes five aliases: value_type, difference_type,
 *     iterator_category, pointer, and reference.
 *   - The commented-out "auto temp{ *it };" shows how auto would simplify this, but
 *     the explicit traits form is what the chapter is illustrating.
 */

#include <print>
#include <vector>
#include <iterator>

using namespace std;

template <typename IteratorType>
void iteratorTraitsTest(IteratorType it)
{
	typename iterator_traits<IteratorType>::value_type temp;
	temp = *it;
	//auto temp{ *it };
	println("{}", temp);
}

int main()
{
	vector v{ 5 };
	iteratorTraitsTest(cbegin(v));
}
