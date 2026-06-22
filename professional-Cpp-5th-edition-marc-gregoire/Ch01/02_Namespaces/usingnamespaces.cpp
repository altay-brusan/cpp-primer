/*
 * Chapter 1 - Namespaces
 *
 * Namespaces partition names so that two libraries can each define foo() without colliding.
 * Wrap declarations in "namespace mycode { ... }" and call them as mycode::foo() using the
 * scope resolution operator "::". A "using namespace mycode;" directive imports every name
 * from that namespace into the current scope; "using mycode::foo;" (a using declaration)
 * imports just one name.
 *
 * Key notes:
 *   - Never put "using namespace X;" or "using X::name;" at global scope in a header - it
 *     leaks into every translation unit that includes the header. Inside a function or a .cpp
 *     it is fine.
 *   - Nested namespaces can be written compactly since C++17: namespace A::B::C { ... }.
 *   - Namespace alias: namespace fs = std::filesystem;
 *   - In C, Standard Library headers end in .h (e.g. <math.h>) and there are no namespaces.
 *     In C++ the .h is dropped (<iostream>) and everything lives in std or a sub-namespace.
 *     The C headers exist in two flavors: <cstdio> (preferred, in std) and <stdio.h> (legacy,
 *     no namespace). Prefer "#include <cstdio>" over "import <cstdio>;" - c-prefixed headers
 *     are not guaranteed to be importable.
 *   - The unnamed/anonymous namespace { ... } gives internal linkage, replacing static at file
 *     scope.
 */

#include <print>

namespace mycode {
	void foo()
	{
		std::println("foo() called in the mycode namespace");
	}
}

using namespace mycode;

int main()
{
	mycode::foo();	// Calls the "foo" function in the "mycode" namespace
	foo();			// implies mycode::foo();
}
