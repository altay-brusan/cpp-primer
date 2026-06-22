/*
 * Chapter 9 - Rvalue References
 *
 * An lvalue is anything you can take the address of - a named variable, an array
 * element, a dereferenced pointer. An rvalue is everything else: literals, the result
 * of `a + b`, the return value of a function that returns by value. `T&` binds only
 * to lvalues; `T&&` (an rvalue reference) binds to rvalues. Overloading on these two
 * forms lets a function know whether its argument is something it can move from
 * cheaply or something it must leave intact.
 *
 * Key notes:
 *   - A named rvalue reference is itself an lvalue. The parameter `string&& message`
 *     has a name, so once inside the function it cannot bind to another `string&&`
 *     parameter unless you re-cast it with `std::move`.
 *   - `std::move` does NOT move anything - it is a cast that turns an lvalue
 *     expression into an rvalue reference, allowing a move-aware overload to be
 *     selected.
 *   - String literals and temporaries like `a + b` bind to the `string&&` overload.
 *   - `string b{ "World" }; handleMessage(b);` would NOT compile if the lvalue
 *     overload were removed - an `string&&` parameter will not bind to a named
 *     variable.
 *   - The `helper` function below illustrates the chain: handleMessage gets an
 *     rvalue reference, but to forward it onward we must move() it again.
 */
#include <print>
#include <string>

using namespace std;

void helper(string&& message)
{
}

// lvalue reference parameter
void handleMessage(string& message)
{
	println("handleMessage with lvalue reference: {}", message);
}

// rvalue reference parameter
void handleMessage(string&& message)
{
	println("handleMessage with rvalue reference: {}", message);
	helper(std::move(message)); // message has a name -> lvalue, must move() to forward
}

int main()
{
	string a{ "Hello " };
	string b{ "World" };

	// Handle a named variable
	handleMessage(a);             // Calls handleMessage(string& value)

	// Handle an expression
	handleMessage(a + b);         // Calls handleMessage(string&& value)

	// Handle a literal
	handleMessage("Hello World"); // Calls handleMessage(string&& value)

	// Handle a named variable and force to use rvalue reference function
	handleMessage(std::move(b));  // Calls handleMessage(string&& value)
}
