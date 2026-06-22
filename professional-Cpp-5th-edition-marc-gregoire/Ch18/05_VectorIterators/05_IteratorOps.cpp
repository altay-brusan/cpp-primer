/*
 * Chapter 18 - Random-Access Iterator Operations
 *
 * A vector iterator is random access, so it supports pointer-like arithmetic:
 * here it += 5 jumps forward, --it steps back, and the resulting element is
 * assigned. Produces no output.
 */

#include <vector>

using namespace std;

int main()
{
	vector<int> intVector(10);

	auto it{ begin(intVector) };
	it += 5;
	--it;
	*it = 4;
}
