/*
 * Chapter 11 - C-style varargs (1/2): printf
 *
 * `printf` is the most familiar example of a variadic function. Format
 * specifiers like `%d` and `%s` tell printf how to interpret each
 * untyped argument off the stack.
 *
 * The downside is that printf has NO type safety - if the format string
 * says `%d` but you pass a string, you get undefined behavior. Compilers
 * (GCC, Clang) ship printf-format checkers as warnings; MSVC has SAL
 * annotations on its CRT.
 *
 * Modern C++ replacement: `std::println` / `std::format`. These use
 * variadic templates instead of C varargs, so they're type-safe and
 * extensible. Sample 02_VarArgs.cpp shows the legacy C-varargs API
 * (`<cstdarg>`) you would only reach for when interoperating with C.
 */
#include <cstdio>

using namespace std;

int main()
{
	printf("int %d\n", 5);
	printf("String %s and int %d\n", "hello", 5);
	printf("Many ints: %d, %d, %d, %d, %d\n", 1, 2, 3, 4, 5);
}
