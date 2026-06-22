/*
 * Chapter 1 - Type Aliases (and typedefs)
 *
 * A type alias gives a new name to an existing type. It does not introduce a new distinct
 * type - the alias and the original are fully interchangeable. The motivating example
 * appears throughout the Standard Library: std::string is itself defined as an alias for
 * std::basic_string<char>.
 *
 * Key notes:
 *   - Modern syntax (C++11): "using Name = Type;" - reads left-to-right, just like a
 *     variable declaration.
 *   - Legacy syntax: "typedef Type Name;" - reads in reverse, easy to misread. Still seen in
 *     C and older C++ codebases.
 *   - Type aliases beat typedefs when used with templates: alias templates
 *     ("template <typename T> using Vec = std::vector<T>;") have no typedef equivalent.
 *   - Aliases do not create new function overload sets or enable distinct behavior - they
 *     are pure renaming. For a genuinely new type with distinct semantics, define a class
 *     or use a strong-typedef library.
 */

#include <vector>
#include <string>

using namespace std;

//void processVector(const vector<basic_string<char>>& vec)
//{
//	// Body omitted
//}

void processVector(const vector<string>& vec)
{
	// Body omitted
}

int main()
{
	//vector<basic_string<char>> myVector;
	vector<string> myVector;
	processVector(myVector);
}
