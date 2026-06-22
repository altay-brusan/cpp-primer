/*
 * Chapter 14 - Catch, Cleanup, and Rethrow
 *
 * An alternative (but discouraged) fix for the leak in 01_BadCode: funcOne()
 * wraps the call to funcTwo() in try { } catch (...), deletes the raw pointer,
 * and rethrows with throw;. It works, but the book notes it is messy and error
 * prone - the delete is duplicated on the normal and exceptional paths - so
 * smart pointers / RAII (see 02_SmartPointer) are preferred.
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
	try {
		funcTwo();
	} catch (...) {
		delete str2;
		throw; // Rethrow the exception.
	}
	delete str2;
}

void funcTwo()
{
	ifstream fileStream;
	fileStream.open("filename");
	throw exception {};
	fileStream.close();
}
