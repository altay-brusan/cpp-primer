/*
 * Chapter 14 - std::source_location Inside a Custom Exception
 *
 * Stores the throw site in a custom exception. MyException takes a
 * source_location parameter defaulted to source_location::current(), so it
 * captures where the exception object was constructed. A where() accessor
 * exposes it, and main() prints the line() and function_name() of the throw
 * site (doSomething()) when handling the exception.
 */

#include <print>
#include <source_location>
#include <string>
#include <exception>
#include <utility>
#include <iostream>

using namespace std;

class MyException : public exception
{
public:
	explicit MyException(string message,
		source_location location = source_location::current())
		: m_message{ move(message) }
		, m_location{ move(location) }
	{
	}

	const char* what() const noexcept override { return m_message.c_str(); }

	virtual const source_location& where() const noexcept { return m_location; }

private:
	string m_message;
	source_location m_location;
};

void doSomething()
{
	throw MyException{ "Throwing MyException." };
}

int main()
{
	try {
		doSomething();
	} catch (const MyException& e) {
		const auto& location{ e.where() };
		println(cerr, "Caught: '{}' at line {} in {}.",
			e.what(), location.line(), location.function_name());
	}
}
