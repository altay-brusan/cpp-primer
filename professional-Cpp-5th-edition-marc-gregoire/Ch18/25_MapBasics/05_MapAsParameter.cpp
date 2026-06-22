/*
 * Chapter 18 - Why map operator[] Is Not const
 *
 * operator[] may insert a new element, so it is not a const member function and
 * cannot be called on a reference-to-const map (the offending line is commented
 * out). To read from a const map, use find() or at() instead.
 */

#include <map>

using namespace std;

void func(const map<int, int>& m)
{
	//println("{}", m[1]);  // Error
}

int main()
{
	map<int, int> m;
	m[1] = 11;
	m[2] = 22;
	m[3] = 33;
	func(m);
}
