/*
 * Chapter 20 - for_each Modifying Elements
 *
 * Demonstrates that std::for_each()'s callback may take a reference-to-non-const
 * parameter and modify the elements in place. The lambda here doubles every
 * element of the vector through a non-const iterator range.
 */

#include <print>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	vector values{ 11, 22, 33, 44 };
	
	// Double each element in the values vector.
	for_each(begin(values), end(values), [](auto& value) { value *= 2; });
	println("{:n}", values);
}
