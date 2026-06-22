/*
 * Chapter 26 - Constraining a Fold with a Variadic Concept
 *
 * Combines fold expressions with concepts: the SameTypes concept itself uses a
 * fold, (same_as<T, Us> && ...), to require that every type in the pack matches
 * T. The constrained sumValues() then folds the values, so mixing types (for
 * example an int with doubles) is rejected at compile time by the requires
 * clause rather than by the arithmetic.
 */

#include <print>
#include <string>
#include <concepts>

using namespace std;

template<typename T, typename... Us>
concept SameTypes = (std::same_as<T, Us> && ...);

template<typename T, typename... Values>
	requires SameTypes<T, Values...>
auto sumValues(const T& init, const Values&... values)
{
	return (init + ... + values);
}

int main()
{
	println("{}", sumValues(1.1, 2.2, 3.3)); // OK: 3 doubles, output is 6.6
	println("{}", sumValues(1));             // OK: 1 integer, output is 1
	println("{}", sumValues("a"s, "b"s));    // OK: 2 strings, output is ab
	//println("{}", sumValues(1, 2.2, 3.3)); // Error
}
