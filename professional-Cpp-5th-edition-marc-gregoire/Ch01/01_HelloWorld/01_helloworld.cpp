// 01_helloworld.cpp

/*
 * Chapter 1 - The Obligatory "Hello, World" Program
 *
 * The smallest meaningful C++ program. It exercises the four things every program needs:
 * comments, bringing in a library (here #include <print>; with C++20 modules this becomes
 * "import <print>;"), the main() function as the entry point, and a way to produce output.
 * main() returns an int that becomes the program's exit status; falling off the end of main()
 * is equivalent to "return 0;", so the explicit return statement here is optional.
 *
 * Key notes:
 *   - // ... is a single-line comment; /  ... / is a block comment (compiler ignores both).
 *   - main() either takes no parameters or takes (int argc, char* argv[]); actual args
 *     start at argv[1] - argv[0] may be the program name or an empty string, do not rely on it.
 *   - Returning void from main() is not allowed; the return type must be int.
 *   - C Standard Library headers come in two forms: <cstdio> (recommended, names in std) and
 *     <stdio.h> (legacy, no namespace). The c-prefixed versions are not guaranteed to be
 *     importable, so prefer "#include <cstdio>" over "import <cstdio>;".
 */

#include <print>

int main()
{
	std::println("Hello, World!");
	return 0;
}
