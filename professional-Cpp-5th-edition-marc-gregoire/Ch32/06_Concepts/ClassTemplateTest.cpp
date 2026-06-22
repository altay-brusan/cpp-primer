/*
 * Chapter 32 - Constraining Template Parameters with Concepts (driver)
 *
 * Wraps an int with the constrained SimpleWrapper, which satisfies the integral
 * constraint. The string-wrapping code is commented out because std::string does not
 * satisfy the floating-point-or-integral constraint and would fail to compile.
 */
#include "SimpleWrapper.h"
#include <print>
#include <string>

using namespace std;

int main()
{
	// Try wrapping an integer.
	int i{ 7 };
	SimpleWrapper intWrapper{ i };
	i = 2;
	println("wrapped value is {}", intWrapper.get());

	// The following now causes a compilation error.
	//string str{ "test" };
	//SimpleWrapper stringWrapper{ str };
	//str += "!";
	//println("wrapped value is {}", stringWrapper.get());
}
