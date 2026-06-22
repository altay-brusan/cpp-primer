/*
 * Chapter 17 - Back Insert Iterator (back_insert_iterator)
 *
 * Shows std::back_insert_iterator, an output iterator adapter that calls push_back()
 * on its container instead of overwriting existing elements. Passing one as the
 * target of myCopy() grows vectorTwo to hold the copied elements, so the destination
 * need not be pre-sized. The active call uses class template argument deduction
 * (back_insert_iterator{ vectorTwo }); the commented lines show the explicit
 * template form and the back_inserter() helper function.
 */

#include <print>
#include <vector>
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
	vector<int> vectorTwo;

	back_insert_iterator<vector<int>> inserter{ vectorTwo };
	//myCopy(cbegin(vectorOne), cend(vectorOne), inserter);

	//myCopy(cbegin(vectorOne), cend(vectorOne), back_inserter(vectorTwo));

	// Using class template argument deduction.
	myCopy(cbegin(vectorOne), cend(vectorOne), back_insert_iterator{ vectorTwo });

	println("{:n}", vectorTwo);
}
