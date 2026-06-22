/*
 * Chapter 19 - std::invoke
 *
 * Demonstrates std::invoke, which calls any callable object with a set of arguments in a
 * uniform way. It is used three times: to call a normal function (printMessage), to call a
 * lambda expression inline, and to call a member function on an object
 * (invoke(&string::size, msg)) - the last showing how invoke handles the
 * pointer-to-member-plus-object case automatically.
 *
 * Key notes:
 *   - invoke shines in generic templated code that must call an arbitrary callable
 *     uniformly; for a known call you would just call it directly.
 */
#include <print>
#include <functional>
#include <string>

using namespace std;

void printMessage(string_view message)
{
	println("{}", message);
}

int main()
{
	invoke(printMessage, "Hello invoke.");
	invoke([](const auto& msg) { println("{}", msg); }, "Hello invoke.");
	string msg{ "Hello invoke." };
	println("{}", invoke(&string::size, msg));
}
