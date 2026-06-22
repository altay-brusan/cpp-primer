/*
 * Chapter 18 - Directly Accessing vector Data
 *
 * A vector stores its elements contiguously, so you can obtain a raw pointer to
 * the underlying block with the data() member function or the non-member
 * std::data(). Produces no output.
 */

#include <vector>

using namespace std;

int main()
{
	vector vec{ 1, 2, 3 };
	int* data1{ vec.data() };
	int* data2{ data(vec) };
}