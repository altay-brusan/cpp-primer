/*
 * Chapter 26 - Variadic Templates with Perfect Forwarding
 *
 * The same recursive processValues() but using forwarding references (T1&&,
 * Tn&&...) together with std::forward in the recursive call. Perfect forwarding
 * preserves the value category of each argument: rvalues stay rvalues and
 * lvalues stay lvalues, avoiding unnecessary copies while still accepting
 * literals.
 *
 * Key notes:
 *   - forward<Tn>(args)... expands the pack, applying std::forward to each
 *     element and separating them with commas.
 */

#include <print>
#include <string>
#include <utility>

using namespace std;

void handleValue(int value) { println("Integer: {}", value); }
void handleValue(double value) { println("Double: {}", value); }
void handleValue(const string& value) { println("String: {}", value); }


void processValues()	// Base case to stop recursion
{
	// Nothing to do in this base case.
}

// Version using forwarding references
template<typename T1, typename... Tn>
void processValues(T1&& arg1, Tn&&... args)
{
	handleValue(forward<T1>(arg1));
	processValues(forward<Tn>(args)...);
}


int main()
{
	processValues(1, 2, 3.56, "test", 1.1f);
}
