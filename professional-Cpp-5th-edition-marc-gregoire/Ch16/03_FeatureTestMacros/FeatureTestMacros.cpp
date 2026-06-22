/*
 * Chapter 16 - Standard Library Feature Test Macros and <version>
 *
 * Part of the Standard Library tour: this sample shows how to probe what your
 * Standard Library implementation supports at compile time using feature test
 * macros. Including <version> exposes all the __cpp_lib_* macros, and a simple
 * #ifdef on __cpp_lib_constexpr_vector reports whether std::vector can be used
 * in constexpr contexts. Such macros (value formatted as YYYYMM) are mainly
 * useful when writing portable code across compilers and library versions.
 */

#include <print>
#include <version>

using namespace std;

int main()
{
#ifdef __cpp_lib_constexpr_vector
	println("std::vector is constexpr!");
#else
	println("Bummer! std::vector is NOT constexpr!");
#endif
}
