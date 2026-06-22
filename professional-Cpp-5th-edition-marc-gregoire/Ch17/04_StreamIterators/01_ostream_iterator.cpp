/*
 * Chapter 17 - Output Stream Iterator (ostream_iterator)
 *
 * Demonstrates std::ostream_iterator as a destination for an iterator-based
 * algorithm. The generic myCopy() copies a [begin, end) range to a target output
 * iterator. Passing an ostream_iterator<int>{ cout, " " } as the target turns
 * myCopy() into a print routine: each assignment through the iterator writes an
 * element to cout via operator<< followed by the " " delimiter. The same myCopy()
 * is reused both to duplicate a vector and to print it.
 *
 * Key notes:
 *   - myCopy() is constrained with input_iterator and output_iterator concepts.
 */

#include <print>
#include <vector>
#include <iterator>
#include <iostream>
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
	vector myVector{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// Use myCopy() to copy myVector to vectorCopy.
	vector<int> vectorCopy(myVector.size());
	myCopy(cbegin(myVector), cend(myVector), begin(vectorCopy));

	// Use the same myCopy() to print the contents of both vectors.
	myCopy(cbegin(myVector), cend(myVector), ostream_iterator<int> { cout, " " });
	println("");
	myCopy(cbegin(vectorCopy), cend(vectorCopy), ostream_iterator<int> { cout, " " });
	println("");
}
