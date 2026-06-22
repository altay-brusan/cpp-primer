/*
 * Chapter 14 - Function-try-blocks for Constructors
 *
 * Demonstrates a function-try-block, which catches exceptions thrown from a
 * constructor's ctor-initializer (not just its body). MyClass's constructor puts
 * try before the ctor-initializer and the catch after the closing brace; when
 * m_subObject's SubObject constructor throws a runtime_error, the handler frees
 * the already-allocated raw m_data and then - by not rethrowing - lets the
 * runtime automatically rethrow the current exception, which main() catches.
 *
 * Key notes:
 *   - A constructor function-try-block's catch must rethrow or throw anew; if it
 *     does neither, the current exception is rethrown automatically.
 *   - The book advises avoiding function-try-blocks - prefer RAII members
 *     (std::vector, unique_ptr) so no raw cleanup is needed.
 */

#include <print>
#include <iostream>
#include <stdexcept>

using namespace std;

class SubObject
{
	public:
		explicit SubObject(int i)
		{
			throw runtime_error{ "Exception by SubObject ctor" };
		}
};

class MyClass
{
	public:
		MyClass();
	private:
		int* m_data{ nullptr };
		SubObject m_subObject;
};

MyClass::MyClass()
try
	: m_data{ new int[42]{ 1, 2, 3 } }, m_subObject{ 42 }
{
	/* ... constructor body ... */
}
catch (const exception& e)
{
	// Cleanup memory.
	delete[] m_data;
	m_data = nullptr;
	println(cerr, "function-try-block caught: '{}'", e.what());
}

int main()
{
	try {
		MyClass m;
	} catch (const exception& e) {
		println(cerr, "main() caught: '{}'", e.what());
	}
}
