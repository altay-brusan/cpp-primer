/*
 * Chapter 26 - Type-Safe Variable-Length Argument Lists
 *
 * Implements processValues() as a variadic function template using a parameter
 * pack (typename... Tn). It handles the first argument, then recursively calls
 * itself with the remaining pack expanded via args..., with a zero-argument
 * overload acting as the base case that stops the recursion. Each value is
 * dispatched to the correct handleValue() overload, so the whole mechanism is
 * fully type-safe (unlike C-style varargs).
 *
 * Key notes:
 *   - The ellipsis means a parameter pack in the parameter lists, and a pack
 *     expansion when written after args in the call.
 *   - This pass-by-value version copies arguments on every recursive call.
 */

#include <print>
#include <string>

using namespace std;

void handleValue(int value) { println("Integer: {}", value); }
void handleValue(double value) { println("Double: {}", value); }
void handleValue(const string& value) { println("String: {}", value); }


void processValues()	// Base case to stop recursion
{
	// Nothing to do in this base case.
}

// Version using pass-by-value
template<typename T1, typename... Tn>
void processValues(const T1& arg1, const Tn&... args)
{
	handleValue(arg1);
	processValues(args...);
}


int main()
{
	processValues(1, 2, 3.56, "test", 1.1f);
}
