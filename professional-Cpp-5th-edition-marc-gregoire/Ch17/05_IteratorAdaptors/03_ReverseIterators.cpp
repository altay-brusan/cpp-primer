/*
 * Chapter 17 - Reverse Iterators (reverse_iterator)
 *
 * Uses std::reverse_iterator (via rbegin()/rend()) to run the forward-only myFind()
 * algorithm backward through a vector, finding the last matching element instead of
 * the first. Calling myFind() with reverse iterators returns a reverse_iterator. To
 * convert a found reverse_iterator back to a normal position, base() is called, but
 * because base() refers to one element past the one the reverse_iterator denotes,
 * --it2.base() is needed to recover the same element. distance() then reports the
 * forward index of both the first and last matches.
 */

#include <print>
#include <vector>
#include <iterator>
#include <concepts>

using namespace std;

template<input_iterator Iter>
auto myFind(Iter begin, Iter end, const typename iterator_traits<Iter>::value_type& value)
{
	for (auto iter{ begin }; iter != end; ++iter) {
		if (*iter == value) { return iter; }
	}
	return end;
}

int main()
{
	vector myVector{ 11, 22, 33, 22, 11 };

	auto it1{ myFind(begin(myVector), end(myVector), 22) };		    // type of it1 is vector<int>::iterator
	auto it2{ myFind(rbegin(myVector), rend(myVector), 22) };		// type of it2 is vector<int>::reverse_iterator

	if (it1 != end(myVector) && it2 != rend(myVector)) {
		println("Found at position {} going forward.",
			distance(begin(myVector), it1));
		println("Found at position {} going backward.",
			distance(begin(myVector), --it2.base()));
	} else {
		println("Failed to find.");
	}
}
