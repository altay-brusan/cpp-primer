/*
 * Chapter 18 - bitset Bitwise Operators
 *
 * bitset supports the full set of bitwise operators. Two bitsets built from
 * strings of 0s and 1s are combined with the & operator, and the result is
 * shifted left with the <<= operator, behaving just like a real sequence of
 * bits.
 */

#include <print>
#include <bitset>

using namespace std;

int main()
{
	auto str1{ "0011001100" };
	auto str2{ "0000111100" };
	bitset<10> bitsOne{ str1 };
	bitset<10> bitsTwo{ str2 };

	auto bitsThree{ bitsOne & bitsTwo };
	println("{}", bitsThree.to_string());
	bitsThree <<= 4;
	println("{}", bitsThree.to_string());
}
