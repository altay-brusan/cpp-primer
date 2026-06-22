/*
 * Chapter 1 - Pass-by-Reference-to-const
 *
 * "const T&" is the preferred way to pass non-trivial objects into a function. No copy is
 * made (cheap, like a pointer) and the callee cannot mutate the argument (safe). And because
 * the parameter promises not to write, it can bind to temporaries and literals as well.
 *
 * Key notes:
 *   - Rule of thumb: for built-in types (int, double, char), pass by value. For class types
 *     you only read, pass "const T&". When the function needs to modify the argument, pass
 *     "T&" (or return a new value).
 *   - A const reference to a temporary extends the temporary's lifetime to the reference's
 *     lifetime - no dangling reference when binding to a function return value.
 *   - For functions that return objects, prefer returning by value. Modern compilers apply
 *     copy elision / RVO so no copy is actually made. Output parameters of type "T&" are an
 *     older style.
 *   - For non-owning views over data, consider std::string_view (for strings) and std::span
 *     (for contiguous ranges) - cheaper to pass and clearer about intent than "const T&".
 */

#include <print>
#include <string>

using namespace std;

void printString(const string& myString)
{
	println("{}", myString);
}

int main()
{
	string someString{ "Hello World" };
	printString(someString);
	printString("Hello World");  // Passing literals works
}
