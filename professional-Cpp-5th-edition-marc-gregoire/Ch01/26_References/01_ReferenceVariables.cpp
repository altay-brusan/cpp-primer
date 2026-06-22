/*
 * Chapter 1 - Reference Variables, Modifying References, References-to-const
 *
 * A reference is an alias for an existing object. Think of it as another name for the same
 * variable, not a separate entity. "int& r = x;" makes r and x refer to the same memory.
 *
 * Key notes:
 *   - A reference must be initialized at the point of declaration. "int& r;" is a hard
 *     compile error.
 *   - A reference cannot be rebound. "r = y;" assigns y's VALUE to whatever r refers to (in
 *     this example, to x); it does NOT make r refer to y.
 *   - Taking the address of a reference gives the address of the underlying object:
 *     "int* p = &xRef;" is the same as "int* p = &x;".
 *   - References cannot be null and there is no "reference to a reference" type.
 *   - "const int& r" is a reference-to-const: it cannot be used to modify the target, and it
 *     can bind to rvalues (literals, temporaries, function-return values). The compiler then
 *     extends the temporary's lifetime to the reference's lifetime:
 *         const std::string& s = makeString();   // temporary kept alive
 *   - Non-const references cannot bind to temporaries or literals - that is by design, to
 *     stop "swap(3, 4)" silently doing nothing useful.
 *   - References can refer to pointers ("int*& ref = p;"), useful for letting a function
 *     change which object the caller's pointer points to.
 */

#include <string>
#include <utility>

using namespace std;

string getString()
{
	return "Hello world!";
}

int main()
{
	int x{ 3 }, y{ 4 }, z{ 5 };
	int& xRef{ x };
	xRef = 10;
	//  int& emptyRef; // DOES NOT COMPILE!

	xRef = y; // changes value of x to 4. Doesn't make xRef refer to y.

	int& zRef{ z };
	zRef = xRef; // Assigns values, not references

	const int& zRef2{ z };
	//  zRef2 = 4; // DOES NOT COMPILE

	//  int& unnamedRef1{ 5 };   // DOES NOT COMPILE
	const int& unnamedRef2{ 5 }; // Works as expected

	// string& string1{ getString() };    // DOES NOT COMPILE
	const string& string2{ getString() }; // Works as expected

	int* intP{ nullptr };
	int*& ptrRef{ intP };
	ptrRef = new int;
	*ptrRef = 5;
	delete ptrRef; ptrRef = nullptr;

	int* xPtr{ &xRef }; // address of a reference is pointer to value
	*xPtr = 100;

	pair myPair{ "hello", 5 };
	const auto& [theString, theInt] { myPair };  // Decompose into references-to-const
}
