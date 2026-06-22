/*
 * Chapter 18 - Move Semantics with push_back()
 *
 * Contrasts the copying and moving overloads of push_back(). Passing an lvalue
 * copies it into the vector; passing std::move(lvalue) or a temporary invokes
 * push_back(T&&), moving the object instead of copying. After a move the source
 * string is in a valid but unspecified state. Produces no output.
 */

#include <vector>
#include <string>

using namespace std;

int main()
{
	vector<string> vec;

	// push_back will trigger copying
	string myElement(5, 'a');  // Constructs the string "aaaaa"
	vec.push_back(myElement);

	// no copying, due to move semantics
	vec.push_back(move(myElement));
	vec.push_back(string(5, 'a'));
}
