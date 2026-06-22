/*
 * Chapter 1 - [[assume]] (C++23)
 *
 * [[assume(expr)]] is a hard promise to the compiler that some expression is true at that
 * point in the code. The optimizer is free to assume it and generate tighter code (here,
 * "x >= 0" lets a signed division by 32 become a cheap arithmetic shift).
 *
 * Key notes:
 *   - If the assumption is false at run time, the program has undefined behavior. Treat it
 *     like a sharp tool - reserve it for invariants you can prove, not "probably true".
 *   - The expression must not have observable side effects; the compiler is allowed to
 *     evaluate it or not.
 *   - Different from assert(): assert() checks at run time in debug builds. [[assume]] never
 *     checks - it informs the optimizer.
 *   - C++23 feature; older compilers may still support a vendor builtin (__builtin_assume,
 *     __assume) with similar intent.
 */

#include <print>

using namespace std;

int divideBy32(int x)
{
	[[assume(x >= 0)]];
	return x / 32;
}

int main()
{
	println("Result: {}", divideBy32(64));
}
