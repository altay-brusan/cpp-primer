/*
 * Chapter 1 - Null Pointer Constant
 *
 * NULL is a holdover from C: it is just the integer constant 0. That means "func(NULL)"
 * resolves to the int overload, which is almost always wrong when the intent was "pass a
 * null pointer". The C++11 keyword nullptr is a genuine pointer-typed null and selects a
 * pointer overload (or fails to compile, as the commented call below does).
 *
 * Key notes:
 *   - Always use nullptr in new code. Never use 0 or NULL as a pointer value.
 *   - nullptr has its own type, std::nullptr_t, and converts to any pointer type but not to
 *     any arithmetic type.
 *   - In a boolean context, "if (p)" is true when p is not null - the same as "p != nullptr".
 *   - When overloading, providing both func(int) and func(some_pointer_t) makes the
 *     int-vs-pointer distinction explicit; nullptr will pick the pointer overload, NULL will
 *     pick the int.
 */

#include <cstddef>

void func(int i) { /* ... */ }

int main()
{
	func(NULL);
	//func(nullptr); // Compilation error.
}
