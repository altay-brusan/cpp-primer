/*
 * Chapter 20 - Shifting Elements (shift_left / shift_right)
 *
 * Demonstrates the C++20 std::shift_left() and std::shift_right() algorithms,
 * which move elements toward one end of a range by a given number of positions;
 * elements falling off the end are left in a moved-from state. shift_left()
 * returns the new end iterator and shift_right() the new begin iterator, which are
 * used with erase() to trim the vector to its proper size.
 */

#include <print>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	vector values{ 11, 22, 33, 44, 55 };
	println("{:n}", values);

	// Shift elements to the left by 2 positions.
	auto newEnd{ shift_left(begin(values), end(values), 2) };
	// Resize the vector to its proper size.
	values.erase(newEnd, end(values));
	println("{:n}", values);

	// Shift elements to the right by 2 positions.
	auto newBegin{ shift_right(begin(values), end(values), 2) };
	// Resize the vector to its proper size.
	values.erase(begin(values), newBegin);
	println("{:n}", values);
}
