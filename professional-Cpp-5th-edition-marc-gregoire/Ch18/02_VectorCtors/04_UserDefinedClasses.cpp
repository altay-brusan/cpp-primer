/*
 * Chapter 18 - vector of a User-Defined Class
 *
 * vector works with user-defined types too. An empty vector<Element> is
 * created here, where Element is a trivial custom class. The program produces
 * no output; it only demonstrates that the instantiation is valid.
 */

#include <vector>

using namespace std;

class Element
{
};

int main()
{
	vector<Element> elementVector;
}
