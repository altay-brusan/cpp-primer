/*
 * Chapter 11 - extern Variables (driver side)
 *
 * `extern int x;` here is a *declaration*: it tells the compiler "a global
 * `x` of type int exists somewhere; the linker will find it". The actual
 * *definition* (which reserves storage and gives it a value) lives in
 * AnotherFile.cpp.
 *
 * Two-file pattern:
 *   - Declaration with extern (no init)    ->  this file's `extern int x;`
 *   - Definition (storage + optional init) ->  AnotherFile.cpp's `int x{3};`
 *
 * For multi-TU global state, you normally put the `extern` declaration in
 * a header and the bare definition in one .cpp. Defining the same global
 * in two TUs would be an ODR violation - the linker would complain about
 * duplicate symbols.
 */
#include <print>

extern int x;

int main()
{
	std::println("{}", x);
}
