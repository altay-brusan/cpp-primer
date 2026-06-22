/*
 * Chapter 18 - bitset Basics
 *
 * std::bitset<N> is a fixed-length sequence of N bits. Individual bits are
 * changed with set() (and reset() and flip()) or through the proxy returned by
 * operator[], queried with test(), and the whole bitset streams as a string of
 * 0s and 1s.
 *
 * Key notes:
 *   - In the printed/string form the leftmost character is the highest-numbered
 *     bit; the low-order bit is on the right.
 */

#include <print>
#include <bitset>

using namespace std;

int main()
{
	bitset<10> myBitset;

	myBitset.set(3);
	myBitset.set(6);
	myBitset[8] = true;
	myBitset[9] = myBitset[3];

	if (myBitset.test(3)) {
		println("Bit 3 is set!");
	}
	println("{}", myBitset.to_string());
}
