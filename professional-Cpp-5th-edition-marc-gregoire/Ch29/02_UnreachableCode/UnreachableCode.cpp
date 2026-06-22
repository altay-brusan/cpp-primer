/*
 * Chapter 29 - Marking Unreachable Code with std::unreachable()
 *
 * Demonstrates std::unreachable() from <utility>, placed in the default branch of a
 * switch whose argument can only be 0, 1, 2, or 3. Reaching std::unreachable() is
 * undefined behavior, which is precisely the point: it promises the compiler that the
 * default case can never happen, letting the optimizer drop bounds checks and generate
 * tighter code. This is a language-level efficiency hint, not a runtime check.
 *
 * Key notes:
 *   - Only use std::unreachable() where you can guarantee the path truly never runs.
 */

#include <utility>

using namespace std;

void handle0Or2() {}
void handle1() {}
void handle3() {}

void doSomething(int number_that_is_only_0_1_2_or_3)
{
	switch (number_that_is_only_0_1_2_or_3)
	{
	case 0:
	case 2:
		handle0Or2();
		break;
	case 1:
		handle1();
		break;
	case 3:
		handle3();
		break;
	default:
		unreachable();
	}
}

int main()
{
	doSomething(4);
}