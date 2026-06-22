/*
 * Chapter 18 - Accessing Object Fields Through Iterators
 *
 * When elements are objects, the -> operator on an iterator calls methods on
 * the pointed-to element. Here each string in a vector<string> has " there"
 * appended via it->append(). A commented-out range-based for loop shows the
 * more elegant equivalent. Produces no output.
 */

#include <vector>
#include <string>

using namespace std;

int main()
{
	vector<string> stringVector(10, "hello");

	for (auto it{ begin(stringVector) }; it != end(stringVector); ++it) {
		it->append(" there");
	}
/*
	// Using Range-Based for loop
	for (auto& str : stringVector) {
		str.append(" there");
	}
*/
}
