/*
 * Chapter 9 - Using std::exchange
 *
 * `std::exchange(target, new_value)` writes `new_value` into `target` and returns
 * `target`'s old value. Think of it as a one-line "swap, but only one direction" -
 * useful any time you want to read a value and replace it with a known sentinel in
 * the same expression. It is heavily used in move operations to read out a pointer
 * and null it in a single line.
 *
 * Key notes:
 *   - Defined in <utility>.
 *   - The new value can be any type convertible to the target type.
 *   - The returned value is the OLD value of `target`, which you typically assign
 *     into the destination.
 *
 * Example:
 *     m_cells = std::exchange(src.m_cells, nullptr); // grab src's pointer, null it
 */
#include <print>
#include <utility>

using namespace std;

int main()
{
	int a{ 11 };
	int b{ 22 };

	println("Before exchange(): a = {}, b = {}", a, b);

	int returnedValue{ exchange(a, b) };

	println("After exchange():  a = {}, b = {}", a, b);
	println("exchange() returned: {}", returnedValue);
}