/*
 * Chapter 18 - Returning a vector by Value (Move Semantics)
 *
 * All Standard Library containers have move constructors and move assignment
 * operators, so returning a large vector from a function by value is cheap.
 * Assigning the result of createVectorOfSize() triggers a move, not a deep
 * copy. Produces no output.
 */

#include <vector>
#include <cstddef>

using namespace std;

vector<int> createVectorOfSize(size_t size)
{
	vector<int> vec(size);
	for (int contents{ 0 }; auto& i : vec) { i = contents++; }
	return vec;
}

int main()
{
	vector<int> myVector;
	myVector = createVectorOfSize(123);
}
