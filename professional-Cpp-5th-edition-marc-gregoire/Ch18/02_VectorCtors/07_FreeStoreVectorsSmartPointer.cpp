/*
 * Chapter 18 - Allocating a vector on the Free Store
 *
 * A vector can itself live on the heap. make_unique<vector<Element>>(10)
 * allocates a vector of 10 default-constructed Elements and hands back a
 * unique_ptr that owns it. Produces no output.
 */

#include <vector>
#include <memory>

using namespace std;

class Element
{
};

int main()
{
	auto elementVector{ make_unique<vector<Element>>(10) };
}
