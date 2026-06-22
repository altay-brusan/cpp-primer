/*
 * Chapter 17 - Input Stream Iterator (istream_iterator)
 *
 * Uses std::istream_iterator<int> to treat the console as a source range for an
 * algorithm. A generic sum() reads and adds every element of a [begin, end) range.
 * Constructing istream_iterator<int>{ cin } gives the begin iterator; the
 * default-constructed istream_iterator is the end-of-stream iterator. Elements are
 * read with operator>> until end-of-stream, summing an arbitrary count of integers
 * with no explicit input loop.
 *
 * Key notes:
 *   - Requires interactive input: enter whitespace-separated integers, then
 *     Ctrl+Z+Enter (Windows) or Enter+Ctrl+D (Linux) to signal end-of-stream.
 */

#include <print>
#include <iterator>
#include <iostream>
#include <concepts>

using namespace std;

// Calculate the sum of all the elements in a given common range.
template<input_iterator InputIter>
auto sum(InputIter begin, InputIter end)
{
	auto sum{ *begin };
	for (auto iter{ ++begin }; iter != end; ++iter) {
		sum += *iter;
	}
	return sum;
}

int main()
{
	// Calculate the sum of integers read from the console until the end-of-stream is reached.
	// Note:
	//    On Windows, the end-of-stream is reached when pressing Ctrl+Z followed by Enter.
	//    On Linux, the end-of-stream is reached by pressing enter to get a new line, followed by Ctrl+D.
	println("Enter numbers separated by whitespace.");
	println("Press Ctrl+Z followed by Enter to stop.");
	istream_iterator<int> numbersIter{ cin };
	istream_iterator<int> endIter;
	int result{ sum(numbersIter, endIter) };
	println("Sum: {}", result);
}
