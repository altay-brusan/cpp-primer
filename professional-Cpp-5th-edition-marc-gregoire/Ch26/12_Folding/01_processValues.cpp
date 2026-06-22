/*
 * Chapter 26 - Fold Expressions Replacing Recursion
 *
 * Rewrites processValues() as a single variadic function template using a unary
 * right fold over the comma operator: (handleValue(forward<Tn>(args)), ...).
 * The fold expands the pack into a comma-separated sequence of handleValue
 * calls, so no recursion and no base-case overload are needed.
 */

#include <print>
#include <string>
#include <utility>

using namespace std;

void handleValue(int value) { println("Integer: {}", value); }
void handleValue(double value) { println("Double: {}", value); }
void handleValue(const string& value) { println("String: {}", value); }

template<typename... Tn>
void processValues(Tn&&... args)
{
	(handleValue(forward<Tn>(args)), ...);
}

int main()
{
	processValues(1, 2, 3.56, "test", 1.1f);
}