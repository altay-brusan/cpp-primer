/*
 * Chapter 17 - Insert Iterator (insert_iterator)
 *
 * Demonstrates std::insert_iterator, which calls insert(position, element) on its
 * container. Its constructor takes both the container and an initial position hint,
 * making it usable with associative containers like std::set, where elements cannot
 * be overwritten in place. myCopy() fills setOne from a vector, with the set placing
 * each value in sorted order. The active call uses class template argument deduction
 * (insert_iterator{ setOne, begin(setOne) }); commented lines show the explicit form
 * and the inserter() helper.
 */

#include <print>
#include <vector>
#include <set>
#include <iterator>
#include <concepts>

using namespace std;

// Copies a range given by a begin and end iterator to a target range.
template<input_iterator InputIter,
	output_iterator<iter_reference_t<InputIter>> OutputIter>
void myCopy(InputIter begin, InputIter end, OutputIter target)
{
	for (auto iter{ begin }; iter != end; ++iter, ++target) {
		*target = *iter;
	}
}

int main()
{
	vector vectorOne{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	set<int> setOne;

	//insert_iterator<set<int>> inserter{ setOne, begin(setOne) };
	//myCopy(cbegin(vectorOne), cend(vectorOne), inserter);

	//myCopy(cbegin(vectorOne), cend(vectorOne), inserter(setOne, begin(setOne)));

	// Using class template argument deduction.
	myCopy(cbegin(vectorOne), cend(vectorOne), insert_iterator{ setOne, begin(setOne) });

	println("{:n}", setOne);
}
