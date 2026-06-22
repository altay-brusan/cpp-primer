/*
 * Chapter 34 - Detecting Native Byte Ordering (Endianness)
 *
 * Reports whether the current architecture stores multi-byte integers in
 * big-endian (high-order byte first, e.g. PowerPC, SPARC) or little-endian
 * (low-order byte first, e.g. x86) order, using the C++20 std::endian
 * enumeration from <bit>. Byte order only matters when binary data crosses
 * machines (over a network or in a file), so portable code may need to convert
 * to a common ordering such as big-endian network byte order.
 */

#include <print>
#include <bit>

using namespace std;

int main()
{
	switch (endian::native)
	{
	case endian::little:
		println("Native ordering is little-endian.");
		break;
	case endian::big:
		println("Native ordering is big-endian.");
		break;
	}
}