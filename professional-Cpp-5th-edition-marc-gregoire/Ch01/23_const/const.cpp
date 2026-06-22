/*
 * Chapter 1 - The Use of const, and const with Pointers
 *
 * const is a contract: the compiler will reject any code that tries to modify the marked
 * thing. Use it for named constants instead of #define (you get a real type and a real
 * scope), for function parameters that should not be modified, and for member functions
 * that should not change the object.
 *
 * Key notes:
 *   - With pointers, position matters:
 *       const int* ip      pointer to const int (cannot change *ip; can reassign ip).
 *       int const* ip      same as above - different spelling, identical meaning.
 *       int* const ip      const pointer to int (cannot reassign ip; can change *ip).
 *       const int* const   both. Cannot reassign ip and cannot change *ip.
 *   - Read-right-to-left rule: const applies to whatever is directly to its left. The first
 *     const is the exception - it may sit at the start, meaning "const applied to the type
 *     to its right".
 *   - "int* const" must be initialized when declared - you cannot rebind it later.
 *   - constexpr: stronger than const - the value must be computable at compile time. Use it
 *     for things you want available in compile-time contexts (array sizes, template args).
 *   - consteval (C++20): forces compile-time evaluation; an immediate function.
 *   - In C, programs typically use #define for constants; in C++ prefer const/constexpr
 *     because they carry a type and respect scope.
 *
 * Example:
 *     constexpr double PI { 3.14159265358979323846 };
 *     constexpr size_t kBufferSize { 1024 };
 *     int buffer[kBufferSize];   // size known at compile time
 */

#include <string>

const int versionNumberMajor{ 2 };
const int versionNumberMinor{ 1 };
const std::string productName{ "Super Hyper Net Modulator" };
const double PI{ 3.141592653589793238462 };

void func(const int /*param*/)
{
	// Not allowed to change param...
}

void constIntOne()
{
	const int* ip;
	ip = new int[10];
	//  ip[4] = 5; // DOES NOT COMPILE!
}

void constIntTwo()
{
	int const* ip;
	ip = new int[10];
	//  ip[4] = 5; // DOES NOT COMPILE!
}

void constPtrOne()
{
	int* const ip{ nullptr };
	//  ip = new int[10]; // DOES NOT COMPILE!
	ip[4] = 5;	// Error: dereferencing a null pointer
}

void constPtrTwo()
{
	int* const ip{ new int[10] };
	ip[4] = 5;
}

void constIntPtrOne()
{
	int const* const ip{ nullptr };
}

void constIntPtrTwo()
{
	const int* const ip{ nullptr };
}

void manyLevelConst()
{
	const int* const* const* const ip{ nullptr };
}

int main()
{
	int* ip;
	ip = new int[10];
	ip[4] = 5;
}
