/*
 * Chapter 18 - std::get<n>() on an array
 *
 * std::get<n>() retrieves the element at compile-time index n from an array.
 * Because the index is a template argument, the compiler verifies it is in
 * range; an out-of-bounds get (shown commented out) is a compilation error
 * rather than undefined behavior. The array uses CTAD to deduce its type.
 */

#include <print>
#include <array>

using namespace std;

int main()
{
	array myArray{ 11, 22, 33 };  // std::array supports CTAD.
	println("{}", std::get<1>(myArray));
	// println("{}", std::get<10>(myArray));  // BUG! Compilation error!
}