/*
 * Chapter 1 - Functions
 *
 * Three function topics live in this sample. First, declaration vs. definition: a declaration
 * (function prototype) tells the compiler the signature so callers can be compiled; the
 * definition supplies the body. Second, __func__: every function has this implicit local
 * variable containing its own name as a C-string - useful for logging. Third, overloading:
 * several functions can share a name as long as the parameter list differs.
 *
 * Key notes:
 *   - "Function signature" = name + parameter list (the return type is not part of it).
 *     That is why two overloads cannot differ only in return type.
 *   - In C++ an empty parameter list means "no parameters". Writing (void) is a C idiom and
 *     unnecessary in C++.
 *   - Return-type deduction: "auto add(int a, int b) { return a + b; }". All return
 *     statements must yield the same type, and a recursive call must come after a non-
 *     recursive return.
 *   - Default arguments belong in the declaration, not in the definition. They are picked
 *     left-to-right - every parameter after the first defaulted one must also have a default.
 *   - The compiler picks an overload using only the argument types at the call site; return
 *     context is not considered.
 *   - constexpr / consteval functions can run at compile time (consteval guarantees it).
 *   - [[nodiscard]] on the return type warns when callers ignore the return value.
 */

#include <print>

using namespace std;

void myFunction(int i, char c);

void myFunction(int i, char c)
{
	println("The value of i is {}.", i);
	println("The value of c is {}.", c);
}

int addNumbers(int number1, int number2)
{
	println("Entering function {}", __func__);
	return number1 + number2;
}

// With function return type deduction
//auto addNumbers(int number1, int number2)
//{
//	println("Entering function {}", __func__);
//	return number1 + number2;
//}

double addNumbers(double a, double b)
{
	return a + b;
}

int main()
{
	int someInt{ 6 };
	char someChar{ 'c' };
	myFunction(8, 'a');
	myFunction(someInt, 'b');
	myFunction(5, someChar);

	int sum{ addNumbers(5, 3) };

	println("{}", addNumbers(1, 2));        // Calls the integer version
	println("{}", addNumbers(1.11, 2.22));  // Calls the double version
}
