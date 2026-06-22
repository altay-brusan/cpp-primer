/*
 * Chapter 19 - bind with Overloaded Functions
 *
 * Shows the disambiguation problem when binding an overloaded function. Because two
 * overloads of overloaded() exist, bind(overloaded, _1) is ambiguous and will not compile
 * (left commented out). To select a specific overload, the function name is cast to the
 * desired function-pointer type, here (void(*)(float)), before passing it to bind().
 *
 * Key notes:
 *   - No output; this sample is about which forms compile, not run-time behavior.
 */
#include <functional>

using namespace std;

void overloaded(int /* num */) {}
void overloaded(float /* f */) {}

int main()
{
	// Bind overloaded function
	//auto f3{ bind(overloaded, placeholders::_1) };					// ERROR
	auto f4{ bind((void(*)(float))overloaded, placeholders::_1) };	// OK
}

