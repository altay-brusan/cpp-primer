/*
 * Chapter 11 - Anonymous Namespaces (driver/linker side)
 *
 * This TU declares a function `f()` and calls it. The other file
 * (AnotherFile.cpp) DEFINES `f()` inside an anonymous namespace, which gives
 * it *internal linkage* - the linker treats it as belonging only to
 * AnotherFile.cpp, so the symbol referenced here is unresolved.
 *
 * Expected outcome: the program fails at the LINK step with an unresolved
 * external symbol error. The point of the example is to demonstrate that
 * anonymous-namespace functions are not visible to other TUs.
 *
 * To make it link, move `void f();` and its definition out of the
 * anonymous namespace in AnotherFile.cpp.
 */
void f();

int main()
{
	f();
}
