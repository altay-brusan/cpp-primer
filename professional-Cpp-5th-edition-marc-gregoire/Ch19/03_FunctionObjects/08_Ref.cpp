/*
 * Chapter 19 - std::ref with bind for Reference Binding
 *
 * Illustrates that std::bind captures its bound arguments by value by default. incr1
 * binds index directly, so increment() operates on a copy and the original index is
 * unchanged. incr2 wraps the argument with std::ref(index), passing a real reference so
 * the call actually increments the caller's index.
 *
 * Key notes:
 *   - Use std::ref (and std::cref for const) to bind by reference through bind().
 *   - No console output; observe the effect with a debugger.
 */
#include <functional>

using namespace std;

void increment(int& value)
{
	++value;
}

int main()
{
	int index{ 0 };
	increment(index);

	auto incr1{ bind(increment, index) };
	incr1();

	auto incr2{ bind(increment, ref(index)) };
	incr2();
}
