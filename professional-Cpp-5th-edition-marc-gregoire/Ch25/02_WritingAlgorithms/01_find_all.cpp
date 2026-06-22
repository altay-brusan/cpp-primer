/*
 * Chapter 25 - Writing a Custom Standard Library Algorithm (find_all)
 *
 * The Standard Library has no algorithm that returns iterators to every element matching a
 * predicate (find/find_if give only one; copy_if loses positions). This sample writes find_all()
 * to fill that gap, modeled on copy_if(): it walks an input range, invokes the predicate on each
 * element, and writes an iterator to each match through an output iterator. Storing iterators
 * rather than copies preserves each match's position in the source range. The template is
 * constrained with iterator concepts (forward_iterator, output_iterator, indirect_unary_predicate)
 * so it composes cleanly with standard containers and adapters like back_inserter.
 *
 * Key notes:
 *   - std::invoke is used to call the predicate so any callable form works.
 *   - The function returns the output iterator one-past-the-last element written, like copy_if().
 */

#include <print>
#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>

using namespace std;

template <forward_iterator ForwardIterator,
	output_iterator<ForwardIterator> OutputIterator,
	indirect_unary_predicate<ForwardIterator> Predicate>
OutputIterator find_all(ForwardIterator first, ForwardIterator last,
	OutputIterator dest, Predicate pred)
{
	while (first != last) {
		if (invoke(pred, *first)) {
			*dest = first;
			++dest;
		}
		++first;
	}
	return dest;
}

int main()
{
	vector<int> vec{ 5, 4, 5, 4, 10, 6, 5, 8, 10 };
	vector<vector<int>::iterator> matches;

	find_all(begin(vec), end(vec), back_inserter(matches),
		[](int i){ return i == 10; });

	println("Found {} matching elements: ", matches.size());

	for (const auto& it : matches) {
		println("{} at position {}", *it, distance(begin(vec), it));
	}
	println("");
}
