/*
 * Chapter 26 - Type Traits: Querying Type Categories
 *
 * The simplest use of type traits: is_integral and is_class report at compile
 * time whether a type belongs to a category. It shows both the classic
 * trait<T>::value form and the C++17 variable-template shorthand trait_v<T>.
 *
 * Key notes:
 *   - For every trait with a value member there is a matching _v variable
 *     template (is_integral_v, is_class_v, and so on).
 */

#include <print>
#include <type_traits>

using namespace std;

int main()
{
	if (is_integral<int>::value) {
		println("int is integral");
	} else {
		println("int is not integral");
	}

	if (is_class<string>::value) {
		println("string is a class");
	} else {
		println("string is not a class");
	}

	// Using _v helpers.
	if (is_integral_v<int>) {
		println("int is integral");
	} else {
		println("int is not integral");
	}

	if (is_class_v<string>) {
		println("string is a class");
	} else {
		println("string is not a class");
	}
}
