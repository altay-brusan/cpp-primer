/*
 * Chapter 25 - A Modernized Custom Algorithm (find_all with Sentinel and Projection)
 *
 * This is the Ranges-style evolution of the previous find_all(). It generalizes the end of the
 * input range from a matching iterator type to any sentinel_for the iterator, and adds an optional
 * projection (defaulting to std::identity) that is applied to each element before the predicate
 * sees it. These two additions mirror how the std::ranges algorithms are specified, making the
 * custom algorithm a first-class citizen alongside the standard ones.
 *
 * Key notes:
 *   - The predicate is constrained against projected<ForwardIterator, Projection>, the type the
 *     predicate actually receives after projection.
 *   - Both predicate and projection are called via std::invoke, supporting any callable form.
 */

#include <print>
#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>
#include <concepts>

using namespace std;

template <forward_iterator ForwardIterator,
	sentinel_for<ForwardIterator> Sentinel,
	output_iterator<ForwardIterator> OutputIterator,
	typename Projection = std::identity,
	indirect_unary_predicate<projected<ForwardIterator, Projection>> Predicate>
OutputIterator find_all(ForwardIterator first, Sentinel last,
	OutputIterator dest, Predicate pred, Projection proj = {})
{
	while (first != last) {
		if (invoke(pred, invoke(proj, *first))) {
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
		[](int i){ return i == 10; },
		[](int i){ return i * 2; });

	println("Found {} matching elements: ", matches.size());

	for (const auto& it : matches) {
		println("{} at position {}", *it, distance(begin(vec), it));
	}
	println("");
}
