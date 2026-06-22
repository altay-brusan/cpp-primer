/*
 * Chapter 18 - Iterator Safety Pitfalls
 *
 * Deliberately buggy code: it dereferences the end() iterator (which refers to
 * one past the last element, not a valid element) and loops with mismatched
 * iterators from two different vectors. Both are undefined behavior - iterators
 * perform no verification, much like raw pointers.
 *
 * Key notes:
 *   - This is an intentional error demo; running it is undefined behavior
 *     (debug builds of MSVC raise an assertion).
 */

#include <vector>

using namespace std;

int main()
{
	vector<int> intVector;

	auto iter{ end(intVector) };
	*iter = 10; // BUG! iter doesn't refer to a valid element.

	vector<int> vectorOne(10);
	vector<int> vectorTwo(10);
	// BUG! Possible infinite loop.
	for (auto iter{ begin(vectorTwo) }; iter != end(vectorOne); ++iter) {
		/* ... */
	}
}
