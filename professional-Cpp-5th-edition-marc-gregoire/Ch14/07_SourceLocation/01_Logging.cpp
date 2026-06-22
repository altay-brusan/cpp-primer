/*
 * Chapter 14 - std::source_location for Logging
 *
 * The C++20 std::source_location class (from <source_location>) is the
 * object-oriented replacement for __FILE__, __LINE__, and __func__. logMessage()
 * takes a source_location parameter defaulted to source_location::current().
 * The trick is that the default argument is evaluated at the call site, so
 * file_name(), line(), and function_name() report where logMessage() was called
 * (foo()), not where it was defined.
 */

#include <print>
#include <source_location>
#include <string_view>

using namespace std;

void logMessage(string_view message,
	const source_location& location = source_location::current())
{
	println("{}({}): {}: {}", location.file_name(),
		location.line(), location.function_name(), message);
}

void foo()
{
	logMessage("Starting execution of foo().");
}

int main()
{
	foo();
}
