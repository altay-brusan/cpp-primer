/*
 * Chapter 18 - Storing References in a vector
 *
 * Containers use value semantics and cannot hold plain references, so this
 * stores std::reference_wrapper<string> elements created with ref(). Calling
 * get() on a wrapper yields the underlying string, so modifying it through the
 * vector actually changes the original variable. Requires <functional>.
 */

#include <print>
#include <vector>
#include <functional>
#include <string>

using namespace std;

int main()
{
	string str1{ "Hello" };
	string str2{ "World" };

	// Create a vector of references to strings.
	vector<reference_wrapper<string>> vec{ ref(str1) };
	vec.push_back(ref(str2));  // push_back() works as well.

	// Modify the string referred to by the second reference in the vector.
	vec[1].get() += "!";

	// The end result is that str2 is modified.
	println("{} {}", str1, str2);
}