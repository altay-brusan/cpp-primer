/*
 * Chapter 14 - The noexcept Specifier and Operator
 *
 * Distinguishes the noexcept specifier (which marks a function as non-throwing)
 * from the noexcept(expression) operator (which evaluates at compile time to
 * whether a given expression is non-throwing). f1-f4 combine the forms - plain
 * noexcept, noexcept(false), and noexcept(noexcept(...)) - and main() prints the
 * operator result for each, producing 1010.
 *
 * Key notes:
 *   - noexcept == noexcept(true); a noexcept function that throws calls
 *     std::terminate().
 */

#include <print>

using namespace std;

void f1() noexcept {}
void f2() noexcept(false) {}
void f3() noexcept(noexcept(f1())) {}
void f4() noexcept(noexcept(f2())) {}

int main()
{
	println("{} {} {} {}", noexcept(f1()),
		noexcept(f2()),
		noexcept(f3()),
		noexcept(f4()));
}
