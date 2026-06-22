/*
 * Chapter 32 - Writing a Class Template (driver)
 *
 * Exercises the SimpleWrapper class template by wrapping both an int and a string, using
 * class template argument deduction (CTAD) as well as the explicit SimpleWrapper<int>
 * form. Because the wrapper holds a reference, modifying the original after wrapping is
 * reflected through get().
 */
#include "SimpleWrapper.h"
#include <print>
#include <string>

using namespace std;

int main()
{
	// Try wrapping an integer.
	int i{ 7 };
	SimpleWrapper intWrapper{ i };  // Using CTAD.
	// Or without class template argument deduction (CTAD).
	SimpleWrapper<int> intWrapper2{ i };
	i = 2;
	println("wrapped value is {}", intWrapper.get());
	println("wrapped value is {}", intWrapper2.get());

	// Try wrapping a string.
	string str{ "test" };
	SimpleWrapper stringWrapper{ str };
	str += "!";
	println("wrapped value is {}", stringWrapper.get());
}
