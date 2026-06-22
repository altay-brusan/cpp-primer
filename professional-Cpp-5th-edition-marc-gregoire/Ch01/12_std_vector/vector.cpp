/*
 * Chapter 1 - std::vector
 *
 * std::vector<T> (in <vector>) is the Standard Library's dynamic-array container. It owns a
 * contiguous block of memory, grows on demand, and frees the block when it goes out of scope.
 * It is the default container in C++ - reach for vector unless a specific need says otherwise.
 *
 * Key notes:
 *   - push_back(x) appends a copy; emplace_back(args...) constructs in place from args - no
 *     intermediate temporary.
 *   - Growth strategy: when capacity is exceeded the vector reallocates to a larger block
 *     (commonly 2x or 1.5x) and moves/copies the elements. Reallocation invalidates pointers,
 *     references, and iterators to existing elements.
 *   - Call .reserve(n) up front when you know the size; it avoids repeated reallocations.
 *   - .size() is current element count; .capacity() is allocated slots. shrink_to_fit() is a
 *     non-binding request to release excess capacity.
 *   - Element access: v[i] is unchecked, v.at(i) throws std::out_of_range. .front(), .back(),
 *     .data() (raw pointer for C APIs).
 *   - CTAD: with an initializer, "std::vector v { 11, 22 };" deduces vector<int>. "vector v;"
 *     does not work - no initializer means no deduction.
 *   - Use vector<bool> only if you accept its proxy-reference quirks; otherwise prefer
 *     std::vector<char> or std::bitset.
 */

#include <print>
#include <vector>

using namespace std;

int main()
{
	// Create a vector of integers
	vector<int> myVector{ 11, 22 };
	// vector myVector { 11, 22 };  // Using CTAD

	// Add some more integers to the vector using push_back()
	myVector.push_back(33);
	myVector.push_back(44);

	// Access elements
	println("1st element: {}", myVector[0]);
}
