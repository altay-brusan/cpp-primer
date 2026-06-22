/*
 * Chapter 14 - Stack Unwinding and Resource Leaks (Bad Code)
 *
 * Demonstrates the danger of stack unwinding. funcTwo() throws, and control
 * jumps to the handler in main(), unwinding the stack. Destructors of local
 * stack objects (str1, fileStream) run correctly, but the delete str2; line in
 * funcOne() is skipped, leaking the heap-allocated string. Unwinding does not
 * free raw pointers or perform manual cleanup. Fixed in 02 and 03.
 */

#include <print>
#include <fstream>
#include <string>
#include <exception>
#include <iostream>

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
	string* str2{ new string{} };
	funcTwo();
	delete str2;
}

void funcTwo()
{
	ifstream fileStream;
	fileStream.open("filename");
	throw exception {};
	fileStream.close();
}
