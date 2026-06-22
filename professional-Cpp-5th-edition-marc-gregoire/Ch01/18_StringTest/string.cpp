/*
 * Chapter 1 - Strings in C++
 *
 * std::string (in <string>) is the C++ string type. It manages its own storage, grows as
 * needed, and can be passed around like a built-in value. Two flavors exist in the language:
 * the C-style "array of characters terminated by '\0'" and the C++-style wrapper that adds
 * memory management and a rich method surface.
 *
 * Key notes:
 *   - operator[] gives unchecked access to a character; .at(i) bounds-checks and throws.
 *   - Concatenate with + or += (both std::string and string literals work on the right).
 *   - Get a raw const char* with .c_str() - useful for passing to C APIs. Do not save the
 *     pointer past any modification to the string.
 *   - The "s" suffix from std::literals::string_literals turns "abc"s into a std::string.
 *   - For non-owning views over a string (substrings, char ranges) use std::string_view.
 *   - Chapter 2 covers strings and std::format() in depth.
 */

#include <print>
#include <string>

using namespace std;

int main()
{
	string myString{ "Hello, World" };
	println("The value of myString is {}", myString);
	println("The second letter is {}", myString[1]);
}
