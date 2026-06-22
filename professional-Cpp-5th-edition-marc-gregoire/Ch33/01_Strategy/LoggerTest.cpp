/*
 * Chapter 33 - Dependency Injection in Action
 *
 * Driver demonstrating the Dependency Injection pattern. The Foo class does not
 * create a logger itself; instead it receives an ILogger pointer through its
 * constructor and uses it via the interface. main() builds a concrete Logger and
 * injects it into Foo, so Foo stays decoupled from the concrete logging type and
 * could just as easily be given a different logger or a test double.
 *
 * Key notes:
 *   - Foo validates the injected pointer and throws if it is null.
 *   - Contains main(); run as a standalone program (writes to log.out).
 */

#include "Logger.h"
#include <stdexcept>

using namespace std;

class Foo
{
public:
	explicit Foo(ILogger* logger) : m_logger{ logger }
	{
		if (m_logger == nullptr) {
			throw invalid_argument{ "ILogger cannot be null." };
		}
	}

	void doSomething()
	{
		m_logger->log("Hello strategy!", ILogger::LogLevel::Info);
	}

private:
	ILogger* m_logger;
};

int main()
{
	Logger concreteLogger{ "log.out" };
	concreteLogger.setLogLevel(ILogger::LogLevel::Debug);

	Foo f{ &concreteLogger };
	f.doSomething();
}
