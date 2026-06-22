/*
 * Chapter 14 - Nested Exceptions
 *
 * Shows how to preserve a first exception while throwing a second. doSomething()
 * catches a runtime_error and uses std::throw_with_nested() to throw a custom
 * MyException with the original nested inside it. main() catches MyException and
 * recovers the inner exception with std::rethrow_if_nested() (the commented-out
 * block shows the equivalent manual dynamic_cast to nested_exception plus
 * rethrow_nested()).
 *
 * Key notes:
 *   - throw_with_nested() synthesizes a type deriving from both
 *     std::nested_exception and MyException; the nested_exception captures the
 *     current exception via current_exception() into an exception_ptr.
 */

#include <print>
#include <string>
#include <utility>
#include <exception>
#include <stdexcept>

using namespace std;

class MyException : public exception
{
public:
	explicit MyException(string message) : m_message{ move(message) } {}
	const char* what() const noexcept override { return m_message.c_str(); }

private:
	string m_message;
};


void doSomething()
{
	try {
		throw runtime_error{ "A runtime_error exception" };
	} catch (const runtime_error& /*e*/) {
		println("doSomething() caught a runtime_error");
		println("doSomething() throwing MyException");
		throw_with_nested(MyException{ "MyException with nested runtime_error" });
	}
}

int main()
{
	try {
		doSomething();
	} catch (const MyException& e) {
		println("main() caught MyException: {}", e.what());

/*		const auto* nested{dynamic_cast<const nested_exception*>(&e)};
		if (nested) {
			try {
				nested->rethrow_nested();
			} catch (const runtime_error& e) {
				// Handle nested exception.
				println("  Nested exception: {}", e.what());
			}
		}
*/
		try {
			rethrow_if_nested(e);
		} catch (const runtime_error& e) {
			// Handle nested exception.
			println("  Nested exception: {}", e.what());
		}
	}
}
