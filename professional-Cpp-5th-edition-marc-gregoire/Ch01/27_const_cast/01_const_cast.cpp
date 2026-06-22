/*
 * Chapter 1 - const_cast()
 *
 * const_cast<T>() is the only one of the five C++ casts that can add or strip const-ness.
 * Typical legitimate use: a function whose own signature is "const char*" but which must
 * forward the argument to a third-party API that takes a plain "char*" and is known not to
 * modify it.
 *
 * Key notes:
 *   - The five casts: static_cast, const_cast, reinterpret_cast, dynamic_cast,
 *     std::bit_cast (C++20). Each expresses a specific intent. Avoid the catch-all C-style
 *     "(T)x" cast.
 *   - Writing through a pointer obtained by const_cast is undefined behavior if the
 *     underlying object was actually declared const. Only legal when the original object is
 *     non-const and just happens to be reached through a const path.
 *   - const_cast cannot cross unrelated types; it only changes the cv-qualifiers.
 *   - For "I just need a read-only view", do not cast - use a "const T&" or std::as_const().
 */

void thirdPartyLibraryFunction(char* str) {}

void f(const char* str)
{
	thirdPartyLibraryFunction(const_cast<char*>(str));
}

int main()
{
	f("Hello World");
}
