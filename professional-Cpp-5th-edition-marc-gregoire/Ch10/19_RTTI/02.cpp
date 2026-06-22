/*
 * Chapter 10 - RTTI (2/2): typeid(...).name() in logging
 *
 * The legitimate use of `typeid` is to *describe* a type, not to switch on it.
 * Here we just want each logged line tagged with its dynamic type name.
 *
 * Key notes:
 *   - The string returned by `type_info::name()` is implementation-defined.
 *     With MSVC it's mangled but readable (e.g. "class Foo"). With GCC/Clang
 *     it's the Itanium-mangled form ("3Foo"); you can demangle it with
 *     abi::__cxa_demangle if you really want readable output.
 *   - Don't parse the string for logic. Treat it as opaque debugging info.
 */
#include <print>
#include <string>

using namespace std;

class Loggable
{
public:
	virtual ~Loggable() = default;
	virtual string getLogMessage() const = 0;
};

class Foo : public Loggable
{
public:
	string getLogMessage() const override { return "Hello logger."; }
};

void logObject(const Loggable& loggableObject)
{
	print("{}: ", typeid(loggableObject).name());     // implementation-defined name
	println("{}", loggableObject.getLogMessage());
}

int main()
{
	Foo f;
	logObject(f);
}
