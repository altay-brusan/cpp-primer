/*
 * Chapter 18 - string as a Sequential Container
 *
 * A std::string behaves like a sequential container of characters: it provides
 * begin() and end(), insert(), push_back(), and the rest of the container
 * basics. The example builds "hello" with insert() and push_back() and
 * traverses it with a range-based for loop and with iterators.
 */

#include <print>
#include <string>

using namespace std;

int main()
{
	string myString;

	myString.insert(cend(myString), 'h');
	myString.insert(cend(myString), 'e');
	myString.push_back('l');
	myString.push_back('l');
	myString.push_back('o');

	for (const auto& letter : myString) {
		print("{}", letter);
	}
	println("");

	for (auto it{ cbegin(myString) }; it != cend(myString); ++it) {
		print("{}", *it);
	}
	println("");
}
