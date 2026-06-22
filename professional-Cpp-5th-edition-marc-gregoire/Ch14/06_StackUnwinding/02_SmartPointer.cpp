/*
 * Chapter 14 - Leak-Safe Unwinding with Smart Pointers
 *
 * The recommended fix for the leak in 01_BadCode: funcOne() holds its dynamic
 * string in a std::unique_ptr created with make_unique instead of a raw pointer.
 * When funcTwo() throws and the stack unwinds, the unique_ptr's destructor runs
 * and frees the memory automatically - an example of RAII guaranteeing cleanup
 * whether the function exits normally or via an exception.
 */

#include <print>
#include <fstream>
#include <string>
#include <exception>
#include <iostream>
#include <memory>

using namespace std;

void funcOne();
void funcTwo();

int main()
{
	try {
		funcOne();
	} catch (const exception& /* e */) {
		println(cerr, "Exception caught!");
		return 1;
	}
}

void funcOne()
{
	string str1;
	auto str2{ make_unique<string>("hello") };
	funcTwo();
}

void funcTwo()
{
	ifstream fileStream;
	fileStream.open("filename");
	throw exception {};
	fileStream.close();
}
