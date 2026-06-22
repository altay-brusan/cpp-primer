/*
 * Chapter 34 - Address (Pointer) Size Differs Across Architectures
 *
 * Prints sizeof a pointer to show that pointer size is tied to the platform's
 * address size, not fixed. On a 32-bit build a pointer is 4 bytes; on a 64-bit
 * build it is 8 bytes. This is a cross-platform pitfall: never assume a pointer
 * is 4 bytes, and never cast a pointer to an integer unless you use the
 * std::intptr_t type from <cstdint>, which is guaranteed large enough.
 */

#include <print>

using namespace std;

int main()
{
	int* ptr{ nullptr };
	println("ptr size is {} bytes", sizeof(ptr));
}
