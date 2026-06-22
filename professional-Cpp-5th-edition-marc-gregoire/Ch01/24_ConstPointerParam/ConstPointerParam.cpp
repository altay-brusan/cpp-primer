/*
 * Chapter 1 - const to Protect Parameters
 *
 * Declaring a pointer parameter as "const T*" tells the caller (and the compiler) that the
 * function will not modify the object the pointer points to. Any assignment through the
 * pointer in the body refuses to compile, which is precisely the safety net you want when
 * passing data across a function or library boundary.
 *
 * Key notes:
 *   - "const T*" vs "T* const": the first protects the pointee from change, the second only
 *     prevents reassigning the pointer itself. Most parameter cases want "const T*" (or a
 *     reference-to-const, see ConstReferenceParameters.cpp).
 *   - A non-const T* will implicitly convert to a const T* at the call site - so callers
 *     pass pointers without any explicit cast.
 *   - Removing const-ness requires an explicit const_cast (covered in 27_const_cast). Do that
 *     only when you are certain the target object is not actually const.
 *   - For built-in parameters that are passed by value (int, double, etc.), "const int x"
 *     prevents the function body from changing its own local copy. Rarely necessary but
 *     occasionally useful for documenting intent.
 */

#include <string>

using namespace std;

void mysteryFunction(const string* someString)
{
	*someString = "Test";  // Will not compile.
}

int main()
{
	string myString{ "The string" };
	mysteryFunction(&myString);  // &myString is a string*
}
