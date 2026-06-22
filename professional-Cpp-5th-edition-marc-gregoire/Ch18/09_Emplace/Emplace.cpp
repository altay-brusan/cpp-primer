/*
 * Chapter 18 - emplace_back()
 *
 * emplace_back() constructs an element directly inside the vector, forwarding
 * its arguments to the element's constructor - no temporary is created and
 * nothing is copied or moved. Here (5, 'a') builds the string "aaaaa" in place.
 * Produces no output.
 */

#include <vector>
#include <string>

using namespace std;

int main()
{
	vector<string> vec;

	vec.emplace_back(5, 'a');
}
